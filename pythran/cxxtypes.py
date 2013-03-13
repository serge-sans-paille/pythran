'''
This module defines classes needed to manipulate c++ types from pythran.
'''
import tables


class Weak:
    """
    Type Qualifier used to represent a weak type

    When a weak type is combined with another type, the weak type is suppressed
    """
    pass


class Type(object):
    """
    A generic type object to be sub-classed

    It maintains a set of qualifiers and
    a tuple of fields used for type comparison.

    The keyword arguments are used to built the internal representation:
    one attribute per key with the associated value
    """
    def __init__(self, **kwargs):
        for k, v in kwargs.iteritems():
            setattr(self, k, v)
        self.qualifiers = self.qualifiers.copy()  # avoid sharing
        self.fields = tuple(sorted(kwargs.keys()))

    def isweak(self):
        return Weak in self.qualifiers

    def __eq__(self, other):
        havesameclass = self.__class__ == other.__class__
        if havesameclass:
            same = lambda x, y: getattr(self, x) == getattr(other, y)
            return all(same(x, y) for x, y in zip(self.fields, other.fields))
        else:
            return False

    def __add__(self, other):
        if isinstance(other, CombinedTypes) and self in other.types:
            return other
        if self.isweak() and not other.isweak():
            return other
        if other.isweak() and not self.isweak():
            return self
        if self == other:
            return self
        return CombinedTypes([self, other])

    def __repr__(self):
        return self.generate(lambda x: x)


class NamedType(Type):
    """
    A generic type object, to hold scalar types and such

    >>> NamedType('long long')
    long long
    """
    def __init__(self, repr, qualifiers=set()):
        super(NamedType, self).__init__(repr=repr, qualifiers=qualifiers)

    def generate(self, ctx):
        return self.repr


class PType(Type):
    """
    A generic parametric type
    """

    prefix = "__ptype{0}"
    count = 0

    def __init__(self, fun, type):
        super(PType, self).__init__(
                fun=fun,
                type=type,
                qualifiers=type.qualifiers,
                name=PType.prefix.format(PType.count)
                )
        PType.count += 1

    def generate(self, ctx):
        return ctx(self.type).generate(ctx)

    def instanciate(self, caller, arguments):
        return InstanciatedType(self.fun,
                self.name,
                arguments,
                caller,
                self.qualifiers)


class InstanciatedType(Type):
    """
    A type instanciated from a parametric type
    """
    def __init__(self, fun, name, arguments, caller, qualifiers):
        super(InstanciatedType, self).__init__(
            fun=fun,
            name=name,
            arguments=arguments,
            qualifiers=qualifiers
            )
        if fun == caller:
            self.qualifiers.add(Weak)

    def generate(self, ctx):
        if self.arguments:
            args = ", ".join(ctx(arg).generate(ctx) for arg in self.arguments)
            template_params = "<{0}>".format(args)
        else:
            template_params = ""

        return "typename {0}::type{1}::{2}".format(
            self.fun.name,
            template_params,
            self.name
            )


class CombinedTypes(Type):
    """
    type resulting from the combination of other types

    >>> NamedType('long') + NamedType('long')
    long
    >>> NamedType('long') + NamedType('char')
    typename __combined<long , char>::type
    """

    def __init__(self, types):
        super(CombinedTypes, self).__init__(
            types=types,
            qualifiers=set.union(*[t.qualifiers for t in types])
            )

    def __add__(self, other):
        if isinstance(other, CombinedTypes):
            stypes = set(self.types)
            types = self.types + [t for t in other.types if t not in stypes]
            return CombinedTypes(types)
        if other in self.types:
            return self
        if other.isweak() and not self.isweak():
            return self
        if self == other:
            return self
        return CombinedTypes(self.types + [other])

    def generate(self, ctx):
        types = " , ".join(ctx(t).generate(ctx) for t in self.types)
        return 'typename __combined<{0}>::type'.format(types)


class ArgumentType(Type):
    """
    A type to hold function arguments

    >>> ArgumentType(4)
    typename std::remove_cv<\
typename std::remove_reference<argument_type4>::type>::type
    """
    def __init__(self, num, qualifiers=set()):
        super(ArgumentType, self).__init__(
                num=num,
                qualifiers=qualifiers)

    def generate(self, ctx):
        argtype = "argument_type{0}".format(self.num)
        noref = "typename std::remove_reference<{0}>::type".format(argtype)
        return "typename std::remove_cv<{0}>::type".format(noref)


class DependentType(Type):
    """
    A class to be sub-classed by any type that depends on another type
    """
    def __init__(self, of):
        super(DependentType, self).__init__(
                of=of,
                qualifiers=of.qualifiers
                )


class Assignable(DependentType):
    """
    A type which can be assigned

    It is used to make the difference between
    * transient types (e.g. generated from expression template)
    * assignable types (typically type of a variable)

    >>> Assignable(NamedType("long"))
    typename assignable<long>::type
    """

    def generate(self, ctx):
        return 'typename assignable<{0}>::type'.format(self.of.generate(ctx))


class DeclType(NamedType):
    """
    Gather the type of a variable

    >>> DeclType("toto")
    decltype(toto)
    """

    def generate(self, ctx):
        return 'decltype({0})'.format(self.repr)


class ContentType(DependentType):
    '''
    Type of the object in a container

    >>> ContentType(DeclType('l'))
    typename content_of<decltype(l)>::type
    '''

    def generate(self, ctx):
        return 'typename content_of<{0}>::type'.format(
                ctx(self.of).generate(ctx))


class IteratorContentType(DependentType):
    '''
    Type of an iterator over the content of a container

    >>> IteratorContentType(NamedType('string'))
    typename std::remove_cv<typename string::iterator::value_type>::type
    '''

    def generate(self, ctx):
        iterator_value_type = ctx(self.of).generate(ctx)
        tn = 'typename '
        return 'typename std::remove_cv<{0}>::type'.format(
            '{0}{1}::iterator::value_type'.format(
                tn * (not iterator_value_type.startswith(tn)),
                iterator_value_type)
            )


class ReturnType(Type):
    '''
    Return type of a call with arguments

    >>> ReturnType(NamedType('math::cos'), [NamedType('float')])
    decltype(std::declval<math::cos>()(std::declval<float>()))
    '''
    def __init__(self, ftype, args):
        args_qualifiers = [arg.qualifiers for arg in args]
        super(ReturnType, self).__init__(
                qualifiers=ftype.qualifiers.union(*args_qualifiers),
                ftype=ftype,
                args=args
                )

    def generate(self, ctx):
        cg = self.ftype.generate(ctx)
        if cg not in tables.builtin_constructors.itervalues():
            cg = 'std::declval<{0}>()'.format(cg)
        args = ("std::declval<{0}>()".format(ctx(arg).generate(ctx))
                for arg in self.args)
        return 'decltype({0}({1}))'.format(cg, ", ".join(args))


class ElementType(Type):
    '''
    Type of the ith element of a tuple or container

    >>> t = TupleType([NamedType('int'), NamedType('str')])
    >>> ElementType(1, t)
    typename std::tuple_element<1,std::tuple<int, str>>::type
    '''

    def __init__(self, index, of):
        super(ElementType, self).__init__(
                qualifiers=of.qualifiers,
                of=of,
                index=index
                )

    def generate(self, ctx):
        return 'typename std::tuple_element<{0},{1}>::type'.format(
                self.index,
                ctx(self.of).generate(ctx))


class AttributeType(ElementType):
    '''
    Type of the ith attribute of an object

    >>> AttributeType(0, NamedType('complex'))
    typename attribute_element<0,complex>::type
    '''

    def generate(self, ctx):
        return 'typename attribute_element<{0},{1}>::type'.format(
                self.index,
                ctx(self.of).generate(ctx))


class ListType(DependentType):
    '''
    Type holding a list of stuff of the same type

    >>> ListType(NamedType('int'))
    core::list<int>
    '''

    def generate(self, ctx):
        return 'core::list<{0}>'.format(ctx(self.of).generate(ctx))


class SetType(DependentType):
    '''
    Type holding a set of stuff of the same type

    >>> SetType(NamedType('int'))
    core::set<int>
    '''

    def generate(self, ctx):
        return 'core::set<{0}>'.format(ctx(self.of).generate(ctx))


class TupleType(Type):
    '''
    Type holding a tuple of stuffs of various types

    >>> TupleType([NamedType('int'), NamedType('bool')])
    std::tuple<int, bool>
    '''
    def __init__(self, ofs):
        if ofs:
            qualifiers = set.union(*[of.qualifiers for of in ofs])
        else:
            qualifiers = set()

        super(TupleType, self).__init__(ofs=ofs, qualifiers=qualifiers)

    def generate(self, ctx):
        if self.ofs:
            elts = (ctx(of).generate(ctx) for of in self.ofs)
            return 'std::tuple<{0}>'.format(", ".join(elts))
        else:
            return 'decltype(std::make_tuple())'


class DictType(Type):
    '''
    Type holding a dict of stuff of the same key and value type

    >>> DictType(NamedType('int'), NamedType('float'))
    core::dict<int,float>
    '''

    def __init__(self, of_key, of_value):
        super(DictType, self).__init__(
                qualifiers=of_key.qualifiers.union(of_value.qualifiers),
                of_key=of_key,
                of_value=of_value
                )

    def generate(self, ctx):
        return 'core::dict<{0},{1}>'.format(
                ctx(self.of_key).generate(ctx),
                ctx(self.of_value).generate(ctx))


class ContainerType(DependentType):
    '''
    Type of any container of stuff of the same type

    >>> ContainerType(NamedType('int'))
    container<int>
    '''

    def generate(self, ctx):
        return 'container<{0}>'.format(ctx(self.of).generate(ctx))


class IndexableType(DependentType):
    '''
    Type of any container indexed by the same type

    >>> IndexableType(NamedType('int'))
    indexable<int>
    '''

    def generate(self, ctx):
        return 'indexable<{0}>'.format(ctx(self.of).generate(ctx))


class ExpressionType(Type):
    '''
    Result type of an operator call

    >>> op = lambda x,y: x + '+' + y
    >>> ExpressionType(op, [NamedType('long'), NamedType('int')])
    decltype(std::declval<long>()+std::declval<int>())
    '''
    def __init__(self, op, exprs):
        super(ExpressionType, self).__init__(
                qualifiers=set.union(*[expr.qualifiers for expr in exprs]),
                op=op,
                exprs=exprs)

    def generate(self, ctx):
        texprs = (ctx(expr).generate(ctx) for expr in self.exprs)
        return 'decltype({0})'.format(
                self.op(*["std::declval<{0}>()".format(t) for t in texprs]))
