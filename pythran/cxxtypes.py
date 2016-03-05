'''
This module defines classes needed to manipulate c++ types from pythran.
'''

from pythran.config import cfg


class Weak:
    """
    Type Qualifier used to represent a weak type

    When a weak type is combined with another type, the weak type is suppressed
    """


class Type(object):
    """
    A generic type object to be sub-classed

    It maintains a set of qualifiers and
    a tuple of fields used for type comparison.

    The keyword arguments are used to built the internal representation:
    one attribute per key with the associated value
    """
    def __init__(self, **kwargs):
        for k, v in kwargs.items():
            setattr(self, k, v)
        self.qualifiers = self.qualifiers.copy()  # avoid sharing
        self.fields = tuple(sorted(kwargs.keys()))
        self.iscore = False

    def isweak(self):
        return Weak in self.qualifiers

    def iscombined(self):
        return False

    def all_types(self):
        return {self}

    def __eq__(self, other):
        havesameclass = self.__class__ == other.__class__
        if havesameclass:
            def same(x, y):
                return getattr(self, x) == getattr(other, y)
            return all(same(x, y) for x, y in zip(self.fields, other.fields))
        else:
            return False

    def __add__(self, other):
        if self.isweak() and not other.isweak():
            return other
        if other.isweak() and not self.isweak():
            return self
        if self == other:
            return self
        if isinstance(other, CombinedTypes) and self in other.types:
            return other
        return CombinedTypes(self, other)

    def __repr__(self):
        return self.generate(lambda x: x)


class NamedType(Type):
    """
    A generic type object, to hold scalar types and such

    >>> NamedType('long long')
    long long
    """
    def __init__(self, srepr, qualifiers=None):
        if qualifiers is None:
            qualifiers = set()
        super(NamedType, self).__init__(srepr=srepr, qualifiers=qualifiers)

    def generate(self, _):
        return self.srepr


class PType(Type):
    """
    A generic parametric type
    """

    prefix = "__ptype{0}"
    count = 0

    def __init__(self, fun, ptype):
        super(PType, self).__init__(fun=fun,
                                    type=ptype,
                                    qualifiers=ptype.qualifiers,
                                    name=PType.prefix.format(PType.count))
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
        super(InstanciatedType, self).__init__(fun=fun,
                                               name=name,
                                               arguments=arguments,
                                               qualifiers=qualifiers)
        if fun == caller:
            self.qualifiers.add(Weak)

    def generate(self, ctx):
        if self.arguments:
            args = ", ".join(ctx(arg).generate(ctx) for arg in self.arguments)
            template_params = "<{0}>".format(args)
        else:
            template_params = ""

        return "typename {0}::type{1}::{2}".format(self.fun.name,
                                                   template_params,
                                                   self.name)


class CombinedTypes(Type):
    """
    type resulting from the combination of other types

    >>> NamedType('long') + NamedType('long')
    long
    >>> NamedType('long') + NamedType('char')
    typename __combined<char,long>::type
    """

    def __init__(self, *types):
        super(CombinedTypes, self).__init__(
            types=types,
            qualifiers=set.union(*[t.qualifiers for t in types])
            )

    def iscombined(self):
        return True

    def __add__(self, other):
        if isinstance(other, CombinedTypes):
            return CombinedTypes(self, other)
        if other in self.types:
            return self
        if other.isweak() and not self.isweak():
            return self
        if self == other:
            return self
        return CombinedTypes(self, other)

    def all_types(self):
        out = set()
        for t in self.types:
            out.update(t.all_types())
        return out

    def generate(self, ctx):
        # gather all underlying types and make sure they do not appear twice
        mct = cfg.getint('typing', 'max_container_type')
        all_types = self.all_types()

        def fot0(t):
            return isinstance(t, IndexableType)

        def fot1(t):
            return isinstance(t, ContainerType)

        def fit(t):
            return not fot0(t) and not fot1(t)

        it = filter(fit, all_types)
        it = sorted(it, key=lambda t: t.iscore, reverse=True)
        ot0 = filter(fot0, all_types)
        ot1 = filter(fot1, all_types)
        icombined = sorted({ctx(t).generate(ctx) for t in it if t.iscore})
        icombined += sorted({ctx(t).generate(ctx) for t in it if not t.iscore})
        lcombined0 = sorted({ctx(t).generate(ctx) for t in ot0})[-mct:]
        lcombined1 = sorted({ctx(t).generate(ctx) for t in ot1})[-mct:]
        combined = icombined + lcombined0 + lcombined1
        if len(combined) == 1:
            return combined[0]
        else:
            return 'typename __combined<{0}>::type'.format(",".join(combined))


class ArgumentType(Type):
    """
    A type to hold function arguments

    >>> ArgumentType(4)
    typename std::remove_cv<\
typename std::remove_reference<argument_type4>::type>::type
    """
    def __init__(self, num, qualifiers=None):
        if qualifiers is None:
            qualifiers = set()
        super(ArgumentType, self).__init__(num=num,
                                           qualifiers=qualifiers)

    def generate(self, _):
        argtype = "argument_type{0}".format(self.num)
        noref = "typename std::remove_reference<{0}>::type".format(argtype)
        return "typename std::remove_cv<{0}>::type".format(noref)


class DependentType(Type):
    """
    A class to be sub-classed by any type that depends on another type
    """
    def __init__(self, of):
        super(DependentType, self).__init__(of=of,
                                            qualifiers=of.qualifiers)

    def iscombined(self):
        return self.of.iscombined()


class Assignable(DependentType):
    """
    A type which can be assigned

    It is used to make the difference between
    * transient types (e.g. generated from expression template)
    * assignable types (typically type of a variable)

    >>> Assignable(NamedType("long"))
    typename pythonic::assignable<long>::type
    """

    def generate(self, ctx):
        return 'typename pythonic::assignable<{0}>::type'.format(
            self.of.generate(ctx))


class Returnable(DependentType):
    """
    A type which can be returned

    It is used to make the difference between
    * returned types (that cannot hold a reference to avoid dangling reference)
    * assignable types (local to a function)

    >>> Returnable(NamedType("long"))
    typename pythonic::returnable<long>::type
    """

    def generate(self, ctx):
        return 'typename pythonic::returnable<{0}>::type'.format(
            self.of.generate(ctx))


class Lazy(DependentType):
    """
    A type which can be a reference

    It is used to make a lazy evaluation of numpy expressions

    >>> Lazy(NamedType("long"))
    typename pythonic::lazy<long>::type
    """

    def generate(self, ctx):
        return 'typename pythonic::lazy<{0}>::type'.format(
            self.of.generate(ctx))


class DeclType(NamedType):
    """
    Gather the type of a variable

    >>> DeclType("toto")
    typename std::remove_cv<\
typename std::remove_reference<decltype(toto)>::type>::type
    """

    def generate(self, _):
        return ('typename std::remove_cv<'
                'typename std::remove_reference<'
                'decltype({0})>::type>::type'.format(self.srepr))


class IteratorContentType(DependentType):
    '''
    Type of an iterator over the content of a container

    >>> IteratorContentType(NamedType('str'))
    typename std::remove_cv<typename std::iterator_traits<\
typename std::remove_reference<str>::type::iterator>::value_type>::type
    '''

    def generate(self, ctx):
        iterator_value_type = ctx(self.of).generate(ctx)
        return 'typename std::remove_cv<{0}>::type'.format(
            'typename std::iterator_traits<{0}>::value_type'.format(
                'typename std::remove_reference<{0}>::type::iterator'.format(
                    iterator_value_type)
                )
            )


class GetAttr(Type):
    '''
    Type of a named attribute

    >>> GetAttr(NamedType('complex'), 'real')
    decltype(pythonic::__builtin__::getattr<pythonic::types::attr::REAL>\
(std::declval<complex>()))
    '''
    def __init__(self, param, attr):
        super(GetAttr, self).__init__(
            qualifiers=param.qualifiers,
            param=param,
            attr=attr)

    def generate(self, ctx):
        return ('decltype(pythonic::__builtin__::getattr<{}>({}))'
                .format('pythonic::types::attr::' + self.attr.upper(),
                        'std::declval<' + self.param.generate(ctx) + '>()'))


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
            args=args)

    def generate(self, ctx):
        # the return type of a constructor is obvious
        cg = self.ftype.generate(ctx)
        cg = 'std::declval<{0}>()'.format(cg)
        args = ("std::declval<{0}>()".format(ctx(arg).generate(ctx))
                for arg in self.args)
        return 'decltype({0}({1}))'.format(cg, ", ".join(args))


class ElementType(Type):
    '''
    Type of the ith element of a tuple or container

    >>> t = TupleType([NamedType('int'), NamedType('str')])
    >>> ElementType(1, t)
    typename std::tuple_element<1,typename std::remove_reference<\
decltype(pythonic::types::make_tuple(std::declval<int>(), \
std::declval<str>()))>::type>::type
    '''

    def __init__(self, index, of):
        super(ElementType, self).__init__(qualifiers=of.qualifiers,
                                          of=of,
                                          index=index)

    def iscombined(self):
        return self.of.iscombined()

    def generate(self, ctx):
        return 'typename std::tuple_element<{0},{1}>::type'.format(
            self.index,
            'typename std::remove_reference<{0}>::type'.format(
                ctx(self.of).generate(ctx)
                )
            )


class ListType(DependentType):
    '''
    Type holding a list of stuff of the same type

    >>> ListType(NamedType('int'))
    pythonic::types::list<int>
    '''

    def generate(self, ctx):
        return 'pythonic::types::list<{0}>'.format(ctx(self.of).generate(ctx))


class SetType(DependentType):
    '''
    Type holding a set of stuff of the same type

    >>> SetType(NamedType('int'))
    pythonic::types::set<int>
    '''

    def generate(self, ctx):
        return 'pythonic::types::set<{0}>'.format(ctx(self.of).generate(ctx))


class TupleType(Type):
    '''
    Type holding a tuple of stuffs of various types

    >>> TupleType([NamedType('int'), NamedType('bool')])
    decltype(pythonic::types::make_tuple(std::declval<int>(), \
std::declval<bool>()))
    '''
    def __init__(self, ofs):
        if ofs:
            qualifiers = set.union(*[of.qualifiers for of in ofs])
        else:
            qualifiers = set()

        super(TupleType, self).__init__(ofs=ofs, qualifiers=qualifiers)

    def iscombined(self):
        return any(of.iscombined() for of in self.ofs)

    def generate(self, ctx):
        elts = (ctx(of).generate(ctx) for of in self.ofs)
        telts = ('std::declval<{0}>()'.format(elt) for elt in elts)
        return 'decltype(pythonic::types::make_tuple({0}))'.format(
            ", ".join(telts))


class DictType(Type):
    '''
    Type holding a dict of stuff of the same key and value type

    >>> DictType(NamedType('int'), NamedType('float'))
    pythonic::types::dict<int,float>
    '''

    def __init__(self, of_key, of_value):
        super(DictType, self).__init__(
            qualifiers=of_key.qualifiers.union(of_value.qualifiers),
            of_key=of_key,
            of_value=of_value
            )

    def iscombined(self):
        return any(of.iscombined() for of in (self.of_key, self.of_value))

    def generate(self, ctx):
        return 'pythonic::types::dict<{0},{1}>'.format(
            ctx(self.of_key).generate(ctx),
            ctx(self.of_value).generate(ctx))


class ContainerType(DependentType):
    '''
    Type of any container of stuff of the same type

    >>> ContainerType(NamedType('int'))
    container<typename std::remove_reference<int>::type>
    '''

    def generate(self, ctx):
        return 'container<typename std::remove_reference<{0}>::type>'.format(
            ctx(self.of).generate(ctx))


class IndexableType(DependentType):
    '''
    Type of any container indexed by the same type

    >>> IndexableType(NamedType('int'))
    indexable<int>
    '''

    def generate(self, ctx):
        return 'indexable<{0}>'.format(ctx(self.of).generate(ctx))


class ExpressionType(Type):

    """
    Result type of an operator call.

    >>> op = lambda x,y: x + '+' + y
    >>> ExpressionType(op, [NamedType('long'), NamedType('int')])
    decltype(std::declval<long>()+std::declval<int>())
    """

    def __init__(self, op, exprs):
        super(ExpressionType, self).__init__(
            qualifiers=set.union(*[expr.qualifiers for expr in exprs]),
            op=op,
            exprs=exprs)

    def iscombined(self):
        return any(expr.iscombined() for expr in self.exprs)

    def generate(self, ctx):
        texprs = (ctx(expr).generate(ctx) for expr in self.exprs)
        return 'decltype({0})'.format(
            self.op(*["std::declval<{0}>()".format(t) for t in texprs]))
