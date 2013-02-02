'''
This module defines classes needed to manipulate c++ types from pythran.
'''
import tables


class Weak:
    pass


def walk_type(obj, cond, op):
    if isinstance(obj, list):
        return [walk_type(o, cond, op) for o in obj]
    elif cond(obj):
        return op(obj)
    elif isinstance(obj, Type):
        # constructs a new object only if necessary.
        # important for type comparison, as they are based on id()
        new = False
        new_attrs = list()
        for attr in obj.fields:
            new_attr = walk_type(getattr(obj, attr), cond, op)
            new = id(getattr(obj, attr)) != id(new_attr)
            new_attrs.append(new_attr)
        if new:
            return type(obj)(*new_attrs)
        else:
            return obj
    else:
        return obj


class Type(object):
    """A generic type object, to hold scalars and such"""
    def __init__(self, repr, qualifiers=None):
        self.repr = repr
        self.qualifiers = qualifiers.copy() if qualifiers else set()
        self.fields = ("repr", "qualifiers",)

    def isweak(self):
        return Weak in self.qualifiers

    def generate(self, ctx):
        return self.repr

    def __eq__(self, other):
        return (self.__class__ == other.__class__
                and all(getattr(self, x) == getattr(other, y)
                    for x, y in zip(self.fields, other.fields)))

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
    """A generic type object, to hold scalars and such"""
    def __init__(self, repr, qualifiers=None):
        Type.__init__(self, repr, qualifiers)
        self.fields = ("repr", "qualifiers",)


class PType(Type):
    prefix = "__ptype{0}"
    count = 0

    """A generic parametric type"""
    def __init__(self, fun, type):
        Type.__init__(self, None, type.qualifiers)
        self.fun = fun
        self.type = type
        self.name = PType.prefix.format(PType.count)
        PType.count += 1
        self.fields = ("fun", "type", "name",)

    def generate(self, ctx):
        return ctx(self.type).generate(ctx)

    def instanciate(self, caller, arguments):
        return InstanciatedType(self.fun,
                self.name,
                arguments,
                caller,
                self.qualifiers)


class InstanciatedType(Type):
    def __init__(self, fun, name, arguments, caller, qualifiers):
        Type.__init__(self, None, qualifiers)
        self.fun = fun
        self.name = name
        self.arguments = arguments
        if fun == caller:
            self.qualifiers.add(Weak)
        self.fields = ("fun", "name", "arguments",)

    def generate(self, ctx):
        return "typename {0}::type{1}::{2}".format(
                self.fun.name,
                "<{0}>".format(", ".join(ctx(arg).generate(ctx)
                    for arg in self.arguments))
                if self.arguments
                else "",
                self.name
                )


class Val(Type):
    """A generic val object, to hold scalars and such"""
    def __init__(self, repr, qualifiers=None):
        Type.__init__(self, repr, qualifiers)


class CombinedTypes(Type):
    def __init__(self, types):
        Type.__init__(self,
                None,
                reduce(set.union, [t.qualifiers for t in types], set()))
        self.types = types
        self.fields = ("types",)

    def __add__(self, other):
        if isinstance(other, CombinedTypes):
            return CombinedTypes(self.types
                    + [t for t in other.types if t not in self.types])
        if other in self.types:
            return self
        if other.isweak() and not self.isweak():
            return self
        if self == other:
            return self
        return CombinedTypes(self.types + [other])

    def generate(self, ctx):
        return 'typename __combined<{0}>::type'.format(
                " , ".join(ctx(t).generate(ctx) for t in self.types))


class RemoveQualifier(Type):
    '''A type without const or reference qualifier'''
    def __init__(self, type_):
        Type.__init__(self, None, type_.qualifiers)
        self.type_ = type_
        self.fields = ("type_", "qualifiers",)

    def generate(self, ctx):
        return "typename std::remove_cv<{0}>::type".format(
            "typename std::remove_reference<{0}>::type".format(
                self.type_.generate(ctx)))


class ArgumentType(Type):
    """A type to hold function arguments"""
    def __init__(self, num, qualifiers=None):
        Type.__init__(self, None, qualifiers)
        self.num = num
        self.fields = ("num", "qualifiers",)

    def generate(self, ctx):
        return "typename std::remove_cv<{0}>::type".format(
            "typename std::remove_reference<{0}>::type".format(
                "argument_type{0}".format(self.num)))


class DeclVal(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'std::declval<{0}>()'.format(ctx(self.of).generate(ctx))


class Assignable(Type):
    """A type which can be assigned"""
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'typename assignable<{0}>::type'.format(self.of.generate(ctx))


class DeclType(Type):
    """Gather the type of a Typed variable"""
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'decltype({0})'.format(self.of.generate(ctx))


class ContentType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'typename content_of<{0}>::type'.format(
                ctx(self.of).generate(ctx))


class IteratorContentType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        iterator_value_type = ctx(self.of).generate(ctx)
        tn = 'typename '
        return 'typename std::remove_cv<{0}>::type'.format(
            '{0}{1}::iterator::value_type'.format(
                tn * (not iterator_value_type.startswith(tn)),
                iterator_value_type)
            )


class ReturnType(Type):
    def __init__(self, call, args):
        Type.__init__(self,
                None,
                reduce(set.union,
                    [arg.qualifiers for arg in args],
                    call.qualifiers))
        self.call = call
        self.args = args
        self.fields = ("call", "args",)

    def generate(self, ctx):
        cg = self.call.generate(ctx)
        if cg not in tables.builtin_constructors.itervalues():
            cg = 'std::declval<{0}>()'.format(cg)
        return 'decltype({0}({1}))'.format(
                cg,
                ", ".join("std::declval<{0}>()".format(ctx(arg).generate(ctx))
                    for arg in self.args))


class ElementType(Type):
    def __init__(self, index, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.index = index
        self.fields = ("index", "of",)

    def generate(self, ctx):
        return 'typename std::tuple_element<{0},{1}>::type'.format(
                self.index,
                ctx(self.of).generate(ctx))


class AttributeType(Type):
    def __init__(self, index, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.index = index
        self.fields = ("index", "of",)

    def generate(self, ctx):
        return 'typename attribute_element<{0},{1}>::type'.format(
                self.index,
                ctx(self.of).generate(ctx))


class ListType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'core::list<{0}>'.format(ctx(self.of).generate(ctx))


class SetType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'core::set<{0}>'.format(ctx(self.of).generate(ctx))


class DictType(Type):
    def __init__(self, of_key, of_value):
        Type.__init__(self, None, of_key.qualifiers.union(of_value.qualifiers))
        self.of_key = of_key
        self.of_value = of_value
        self.fields = ("of_key", "of_value",)

    def generate(self, ctx):
        return 'core::dict<{0},{1}>'.format(
                ctx(self.of_key).generate(ctx),
                ctx(self.of_value).generate(ctx))


class ContainerType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'container<{0}>'.format(ctx(self.of).generate(ctx))


class IndexableType(Type):
    def __init__(self, of):
        Type.__init__(self, None, of.qualifiers)
        self.of = of
        self.fields = ("of",)

    def generate(self, ctx):
        return 'indexable<{0}>'.format(ctx(self.of).generate(ctx))


class TupleType(Type):
    def __init__(self, ofs):
        Type.__init__(self,
                None,
                reduce(set.union, [of.qualifiers for of in ofs], set()))
        self.ofs = ofs
        self.fields = ("ofs",)

    def generate(self, ctx):
        return ('std::tuple<{0}>'.format(
            ", ".join(ctx(of).generate(ctx) for of in self.ofs))
            if self.ofs
            else 'decltype(std::make_tuple())')


class ExpressionType(Type):
    def __init__(self, op, exprs):
        Type.__init__(self,
                None,
                reduce(set.union, (expr.qualifiers for expr in exprs), set()))
        self.op = op
        self.exprs = exprs
        self.fields = ("op", "exprs",)

    def generate(self, ctx):
        return 'decltype({0})'.format(
                self.op(
                    *["std::declval<{0}>()".format(ctx(expr).generate(ctx))
                        for expr in self.exprs]))
