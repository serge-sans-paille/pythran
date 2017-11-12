from six import with_metaclass


class FunMeta(type):

    def __getitem__(cls, item):
        return Fun(tuple(item[0]) + (item[1],))


class DictMeta(type):

    def __getitem__(cls, item):
        return Dict(item)


class UnionMeta(type):

    def __getitem__(cls, item):
        return Union(item)


class SetMeta(type):

    def __getitem__(cls, item):
        return Set(item)


class ListMeta(type):

    def __getitem__(cls, item):
        return List(item)


class IterableMeta(type):

    def __getitem__(cls, item):
        return Iterable(item)


class GeneratorMeta(type):

    def __getitem__(cls, item):
        return Generator(item)


class TupleMeta(type):

    def __getitem__(cls, item):
        return Tuple(item)


class OptionalMeta(type):

    def __getitem__(cls, item):
        return Optional(item)


class NDArrayMeta(type):

    def __getitem__(cls, item):
        return NDArray(item)


class PointerMeta(type):

    def __getitem__(cls, item):
        return Pointer(item)


class Type(type):

    def __new__(cls, args):
        return type.__new__(
            cls,
            cls.__name__,
            (object,),
            {'__args__': args if isinstance(args, tuple) else (args,)}
        )

    def __init__(self, *args, **kwargs):
        pass


class Fun(with_metaclass(FunMeta, Type)):
    pass


class Dict(with_metaclass(DictMeta, Type)):
    pass


class Union(with_metaclass(UnionMeta, Type)):
    pass


class Set(with_metaclass(SetMeta, Type)):
    pass


class List(with_metaclass(ListMeta, Type)):
    pass


class Iterable(with_metaclass(IterableMeta, Type)):
    pass


class Generator(with_metaclass(GeneratorMeta, Type)):
    pass


class Tuple(with_metaclass(TupleMeta, Type)):
    pass


class Optional(with_metaclass(OptionalMeta, Type)):
    pass


class NDArray(with_metaclass(NDArrayMeta, Type)):
    pass


class Pointer(with_metaclass(PointerMeta, Type)):
    pass


class TypeVar(object):

    def __init__(self, name):
        self.__name__ = name


class Sized(object):
    pass


class Any(object):
    pass


class File(object):
    pass
