'''
This module defines classes needed to manipulate c++ types from pythran.
'''

from pythran.config import cfg


class Type(object):
    """
    A generic type object to be sub-classed

    The keyword arguments are used to built the internal representation:
    one attribute per key with the associated value
    """
    def __init__(self, **kwargs):
        for k, v in kwargs.items():
            if isinstance(v, list):
                v = tuple(v)
            setattr(self, k, v)
        self.iscore = False

    def iscombined(self):
        return False

    def all_types(self):
        return {self}

    def __add__(self, other):
        if self == other:
            return self
        if isinstance(other, CombinedTypes) and self in other.types:
            return other
        return CombinedTypes(self, other)

    def __repr__(self):
        return self.generate(lambda x: x)

UnknownType = Type()


class NamedType(Type):
    """
    A generic type object, to hold scalar types and such

    >>> NamedType('long long')
    long long
    """
    def __init__(self, srepr):
        super(NamedType, self).__init__(srepr=srepr)

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
                                    name=PType.prefix.format(PType.count))
        PType.count += 1

    def generate(self, ctx):
        return ctx(self.type).generate(ctx)

    def instanciate(self, caller, arguments):
        if self.fun is caller:
            return UnknownType
        else:
            return InstanciatedType(self.fun, self.name, arguments)


class InstanciatedType(Type):
    """
    A type instanciated from a parametric type
    """
    def __init__(self, fun, name, arguments):
        super(InstanciatedType, self).__init__(fun=fun,
                                               name=name,
                                               arguments=arguments)

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
        super(CombinedTypes, self).__init__(types=types)
        self._all_types = None  # cached, much faster

    def iscombined(self):
        return True

    def __add__(self, other):
        if isinstance(other, CombinedTypes):
            return CombinedTypes(self, other)
        if other in self.types:
            return self
        if self == other:
            return self
        return CombinedTypes(self, other)

    def all_types(self):
        if self._all_types is None:
            self._all_types = set()
            self._all_types.update(*[t.all_types() for t in self.types])
            if UnknownType in self._all_types and len(self._all_types) > 1:
                self._all_types.pop(UnknownType)
        return self._all_types

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

        it = [t for t in all_types if fit(t)]
        it = sorted(it, key=lambda t: t.iscore, reverse=True)
        ot0 = [t for t in all_types if fot0(t)]
        ot1 = [t for t in all_types if fot1(t)]
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
    def __init__(self, num):
        super(ArgumentType, self).__init__(num=num)

    def generate(self, _):
        argtype = "argument_type{0}".format(self.num)
        noref = "typename std::remove_reference<{0}>::type".format(argtype)
        return "typename std::remove_cv<{0}>::type".format(noref)


class DependentType(Type):
    """
    A class to be sub-classed by any type that depends on another type
    """
    def __init__(self, of):
        assert of is not None
        super(DependentType, self).__init__(of=of)

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


class IteratorOfType(DependentType):
    '''
    Type of an Iterator of a container
    >>> IteratorOfType(NamedType('some'))
    typename some::iterator
    >>> IteratorOfType(NamedType('typename some::stuff'))
    typename some::stuff::iterator
    '''
    def generate(self, ctx):
        container_type = ctx(self.of).generate(ctx)
        if container_type.startswith('typename'):
            return container_type + '::iterator'
        else:
            return 'typename ' + container_type + '::iterator'


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
        super(GetAttr, self).__init__(param=param, attr=attr)

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
        super(ReturnType, self).__init__(ftype=ftype, args=args)

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
        super(ElementType, self).__init__(of=of, index=index)

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
        super(TupleType, self).__init__(ofs=ofs)

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
        super(DictType, self).__init__(of_key=of_key, of_value=of_value)

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
        super(ExpressionType, self).__init__(op=op, exprs=exprs)

    def iscombined(self):
        return any(expr.iscombined() for expr in self.exprs)

    def generate(self, ctx):
        texprs = (ctx(expr).generate(ctx) for expr in self.exprs)
        return 'decltype({0})'.format(
            self.op(*["std::declval<{0}>()".format(t) for t in texprs]))
