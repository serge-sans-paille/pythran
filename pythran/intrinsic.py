'''
This module contains all classes used to model intrinsics behavior.
'''

from pythran.conversion import to_ast

import ast


class UpdateEffect(object):
    pass


class ReadEffect(object):
    pass


class ReadOnceEffect(ReadEffect):
    pass


class Intrinsic(object):
    '''
    Model any Method/Function

    Its member variables are:

    - argument_effects that describes the effect of the function on its
      argument (either UpdateEffect, ReadEffect or ReadOnceEffect)
    - global_effects that describes wether the function has side effects
    - return_alias that describes the aliasing between the return value
      and the parameters. The lambda returns an ast expression, generally
      depending on the node arguments (see dict.setdefault)
    - args that describes the name and default value of each arg, using the
      same representation as ast.FunctionDef, i.e. ast.arguments
    '''
    def __init__(self, **kwargs):
        self.argument_effects = kwargs.get('argument_effects',
                                           (UpdateEffect(),) * 11)
        self.global_effects = kwargs.get('global_effects', False)
        self.return_alias = kwargs.get('return_alias', lambda x: {None})
        self.args = ast.arguments([ast.Name(n, ast.Param())
                                   for n in kwargs.get('args', [])],
                                  None, None,
                                  map(to_ast, kwargs.get('defaults', [])))

    def isliteral(self):
        return False

    def isfunction(self):
        return False

    def isstaticfunction(self):
        return False

    def ismethod(self):
        return False

    def isattribute(self):
        return False

    def isconst(self):
        return not any(
            isinstance(x, UpdateEffect) for x in self.argument_effects
            ) and not self.global_effects

    def isreadonce(self, n):
        return isinstance(self.argument_effects[n], ReadOnceEffect)

    def combiner(self, s, node):
        pass


class FunctionIntr(Intrinsic):
    def __init__(self, **kwargs):
        kwargs.setdefault('combiners', ())
        super(FunctionIntr, self).__init__(**kwargs)
        self.combiners = kwargs['combiners']

    def isfunction(self):
        return True

    def isstaticfunction(self):
        return True

    def add_combiner(self, _combiner):
        self.combiners += (_combiner,)

    def combiner(self, s, node):
        for comb in self.combiners:
            comb(s, node)


class UserFunction(FunctionIntr):
    def __init__(self, *combiners, **kwargs):
        kwargs.setdefault('return_alias', lambda x: {None})
        kwargs['combiners'] = combiners
        super(UserFunction, self).__init__(**kwargs)


class ConstFunctionIntr(FunctionIntr):
    def __init__(self, **kwargs):
        kwargs.setdefault('argument_effects',
                          (ReadEffect(),) * 10)
        super(ConstFunctionIntr, self).__init__(**kwargs)


class ConstExceptionIntr(ConstFunctionIntr):
    def __init__(self, **kwargs):
        kwargs.setdefault('argument_effects',
                          (ReadEffect(),) * 10)
        super(ConstExceptionIntr, self).__init__(**kwargs)


class ReadOnceFunctionIntr(ConstFunctionIntr):
    def __init__(self):
        super(ReadOnceFunctionIntr, self).__init__(
            argument_effects=(ReadOnceEffect(),) * 11)


class MethodIntr(FunctionIntr):
    def __init__(self, *combiners, **kwargs):
        kwargs.setdefault('argument_effects',
                          (UpdateEffect(),) + (ReadEffect(),) * 10)
        kwargs['combiners'] = combiners
        super(MethodIntr, self).__init__(**kwargs)

    def ismethod(self):
        return True

    def isstaticfunction(self):
        return False


class ConstMethodIntr(MethodIntr):
    def __init__(self, *combiners):
        super(ConstMethodIntr, self).__init__(
            *combiners,
            argument_effects=(ReadEffect(),) * 12)


class AttributeIntr(Intrinsic):
    def __init__(self, val):
        self.val = val
        super(AttributeIntr, self).__init__()

    def isattribute(self):
        return True


class ConstantIntr(Intrinsic):
    def __init__(self):
        super(ConstantIntr, self).__init__(argument_effects=())

    def isliteral(self):
        return True


class Class(Intrinsic):
    def __init__(self, d, *args, **kwargs):
        super(Class, self).__init__(*args, **kwargs)
        self.fields = d

    def __getitem__(self, key):
        return self.fields[key]

    def __contains__(self, key):
        """ Forward key content to aliased module. """
        return key in self.fields


class ClassWithReadOnceConstructor(Class, ReadOnceFunctionIntr):
    def __init__(self, d, *args, **kwargs):
        super(ClassWithReadOnceConstructor, self).__init__(d, *args, **kwargs)


class ClassWithConstConstructor(Class, ConstFunctionIntr):
    def __init__(self, d, *args, **kwargs):
        super(ClassWithConstConstructor, self).__init__(d, *args, **kwargs)


class ExceptionClass(Class, ConstExceptionIntr):
    def __init__(self, d, *args, **kwargs):
        super(ExceptionClass, self).__init__(d, *args, **kwargs)
