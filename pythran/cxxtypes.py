'''This module defines all the types needed to maniuplate c++ types used by pythran'''
import tables

class weak:pass

def walk_type(obj, cond, op):
    if isinstance(obj,list): return [ walk_type(o, cond, op) for o in obj ]
    elif cond(obj): return op(obj)
    elif isinstance(obj, Type):
        new=False # constructs a new object only if necessary, important for type comparison, as they are based on id()
        new_attrs=list()
        for attr in obj.fields:
            new_attr = walk_type(getattr(obj,attr), cond, op)
            new= id(getattr(obj,attr)) != id(new_attr)
            new_attrs.append(new_attr)
        if new:
            return type(obj)(*new_attrs)
        else: return obj
    else: return obj

class Type(object):
    """A generic type object, to hold scalars and such"""
    def __init__(self, repr,qualifiers=None):
        self.repr=repr
        self.qualifiers=set(qualifiers) if qualifiers else set()
        self.fields=("repr","qualifiers")

    def generate(self): return self.repr

    def __eq__(self, other):
        return self.__class__==other.__class__ and all( [ getattr(self,x)==getattr(other,y) for x,y in zip(self.fields, other.fields) ])

    def __add__(self, other):
        if isinstance(other, CombinedTypes) and self in other.types: return other
        if weak in self.qualifiers and weak not in other.qualifiers: return other
        if weak in other.qualifiers and weak not in self.qualifiers: return self
        if self == other: return self
        return CombinedTypes([self, other])

    def __repr__(self): return self.generate()


class Val(Type):
    """A generic val object, to hold scalars and such"""
    def __init__(self, repr,qualifiers=None):
        Type.__init__(self,repr,qualifiers)
    def __add__(self, other):assert(False)


class CombinedTypes(Type):
    def __init__(self, types):
        self.types=types
        self.qualifiers=reduce(set.union, [ t.qualifiers for t in types ], set())
        self.fields=("types",)

    def __add__(self, other):
        if len(self.types) > 10: return self # this is a ward: the grater the value the longer the compilation time...
        if isinstance(other, CombinedTypes):
            return CombinedTypes(self.types + [ t for t in other.types if t not in self.types ])
        if other in self.types: return self
        if weak in other.qualifiers and weak not in self.qualifiers: return self
        if self == other: return self
        return CombinedTypes(self.types+[other])

    def generate(self):
        return 'decltype({0})'.format(" + ".join('std::declval<{0}>()'.format(t.generate()) for t in self.types ))

class ArgumentType(Type):
    """A type to hold function arguments"""
    def __init__(self,num,qualifiers=None):
        self.num=num
        self.qualifiers=set(qualifiers) if qualifiers else set()
        self.fields=("num","qualifiers")

    def generate(self): return "argument_type{0}".format(self.num)

class DeclVal(Type):
    def __init__(self, of):
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("of",)
    def generate(self):
        return 'std::declval<{0}>()'.format(self.of.generate())

class DeclType(Type):
    """Gather the type of a Typed variable"""
    def __init__(self, of):
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("of",)
    def generate(self):
        return 'decltype({0})'.format(self.of.generate())

class ContentType(Type):
    def __init__(self, of):
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("of",)
    def generate(self):
        return 'typename content_of<{0}>::type'.format(self.of.generate())

class ReturnType(Type):
    def __init__(self, call, args):
        self.call=call
        self.args=args
        self.qualifiers=reduce(set.union, [ arg.qualifiers for arg in args ], call.qualifiers)
        self.fields=("call", "args",)
    def generate(self):
        cg = self.call.generate()
        if cg not in tables.builtin_constructors.itervalues(): cg = 'std::declval<{0}>()'.format(cg)
        return 'decltype({0}({1}))'.format(cg, ", ".join("std::declval<{0}>()".format( arg.generate() ) for arg in self.args))

class ElementType(Type):
    def __init__(self, index, of):
        self.index=index
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("index", "of",)
    def generate(self):
        return 'typename std::tuple_element<{0},{1}>::type'.format(self.index, self.of.generate())

class SequenceType(Type):
    def __init__(self, of):
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("of",)
    def generate(self):
        return 'sequence<{0}>'.format(self.of.generate())

class ContainerType(Type):
    def __init__(self, of):
        self.of=of
        self.qualifiers=of.qualifiers
        self.fields=("of",)
    def generate(self):
        return 'container<{0}>'.format(self.of.generate())

class TupleType(Type):
    def __init__(self, ofs):
        self.ofs=ofs
        self.qualifiers=reduce(set.union, [ of.qualifiers for of in ofs ], set())
        self.fields=("ofs",)
    def generate(self):
        return 'std::tuple<{0}>'.format(", ".join(of.generate() for of in self.ofs)) if self.ofs else 'decltype(std::make_tuple())'

class ExpressionType(Type):
    def __init__(self, op, exprs):
        self.op=op
        self.exprs=exprs
        self.qualifiers=reduce(set.union, [ expr.qualifiers for expr in exprs ], set())
        self.fields=("op", "exprs",)
    def generate(self):
        return 'decltype({0})'.format(self.op(*["std::declval<{0}>()".format(expr.generate()) for expr in self.exprs]))

