class UpdateEffect(object):pass
class ReadEffect(object):pass

class Intrinsic:
    def __init__(self, effects=None):
        self.effects = effects or ( UpdateEffect(), ) + ( ReadEffect(), ) * 11

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
        return any( isinstance(x, UpdateEffect) for x in self.effects )

class FunctionIntr(Intrinsic):
    def __init__(self, effects=None):
        Intrinsic.__init__(self,effects)

    def isfunction(self):
        return True

    def isstaticfunction(self):
        return True

class ConstFunctionIntr(Intrinsic):
    def __init__(self):
        Intrinsic.__init__(self, effects=() )

class MethodIntr(FunctionIntr):
    def __init__(self,_combiner = [], effects=None):
        FunctionIntr.__init__(self, effects)
        self.combinerList = _combiner

    def addCombiner(self,_combiner):
        self.combinerList = self.combinerList + _combiner
        #self.combinerList.extend(_combiner)

    def combiner(self,s,node):
        for comb in self.combinerList:
            comb(s,node)

    def ismethod(self):
        return True

    def isstaticfunction(self):
        return False

class ConstMethodIntr(MethodIntr):
    def __init__(self,_combiner = []):
        FunctionIntr.__init__(self, ( ReadEffect() , ) *12 )
        self.combinerList = _combiner

class AttributeIntr(Intrinsic):
    def __init__(self,_val, effects=None):
        Intrinsic.__init__(self, effects)
        self.val = _val

    def isattribute(self):
        return True

class ScalarIntr(Intrinsic):
    def __init__(self, effects=None):
        Intrinsic.__init__(self, effects)

    def isscalar(self):
        return True
