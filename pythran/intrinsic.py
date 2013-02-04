'''
This module contains all classes used to model intrinsics behavior.
'''


class UpdateEffect(object):
    pass


class ReadEffect(object):
    pass


class Intrinsic:
    def __init__(self, argument_effects=(UpdateEffect(),) * 11,
            global_effects=False,
            return_alias=lambda x: {None}):
        self.argument_effects = argument_effects
        self.global_effects = global_effects
        self.return_alias = return_alias

    def isscalar(self):
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


class FunctionIntr(Intrinsic):
    def __init__(self, argument_effects=(UpdateEffect(),) * 11,
            global_effects=False,
            return_alias=lambda x: {None}):
        Intrinsic.__init__(self,
                argument_effects,
                global_effects,
                return_alias)

    def isfunction(self):
        return True

    def isstaticfunction(self):
        return True


class UserFunction(FunctionIntr):
    def __init__(self, *combiners, **kwargs):
        FunctionIntr.__init__(self, (UpdateEffect(),) + (ReadEffect(),) * 10,
                return_alias=kwargs.get('return_alias', set()))
        self.combiners = combiners

    def add_combiner(self, _combiner):
        self.combiners += (_combiner,)

    def combiner(self, s, node):
        for comb in self.combiners:
            comb(s, node)


class ConstFunctionIntr(FunctionIntr):
    def __init__(self):
        FunctionIntr.__init__(self, argument_effects=())


class MethodIntr(FunctionIntr):
    def __init__(self, *combiners, **kwargs):
        FunctionIntr.__init__(self, (UpdateEffect(),) + (ReadEffect(),) * 10,
                return_alias=kwargs.get('return_alias', lambda x: {None}))
        self.combiners = combiners

    def add_combiner(self, _combiner):
        self.combiners += (_combiner,)

    def combiner(self, s, node):
        for comb in self.combiners:
            comb(s, node)

    def ismethod(self):
        return True

    def isstaticfunction(self):
        return False


class ConstMethodIntr(MethodIntr):
    def __init__(self, *combiners):
        FunctionIntr.__init__(self, (ReadEffect(),) * 12)
        self.combiners = combiners


class AttributeIntr(Intrinsic):
    def __init__(self, _val, effects=None):
        Intrinsic.__init__(self, global_effects=False)
        self.val = _val

    def isattribute(self):
        return True


class ScalarIntr(Intrinsic):
    def __init__(self):
        Intrinsic.__init__(self, argument_effects=(), global_effects=False)

    def isscalar(self):
        return True
