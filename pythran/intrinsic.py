class Intrinsic:
    def __init__(self):
        pass

    def isscalar(self):
        return False

    def ismethod(self):
        return False

    def ismethodwithsideeffect(self):
        return False

    def isattribute(self):
        return False

class MethodWithSideEffectIntr(Intrinsic):
    def __init__(self,_combiner = []):
        self.combinerList = _combiner

    def addCombiner(self,_combiner):
        self.combinerList = self.combinerList + _combiner
        #self.combinerList.extend(_combiner)

    def combiner(self,s,node):
        for comb in self.combinerList:
            comb(s,node)

    def ismethodwithsideeffect(self):
        return True

class AttributeIntr(Intrinsic):
    def __init__(self,_val):
        self.val = _val

    def isattribute(self):
        return True

class ScalarIntr(Intrinsic):
    def __init__(self):
        pass

    def isscalar(self):
        return True

class MethodIntr(Intrinsic):
    def __init__(self):
        pass

    def ismethod(self):
        return True
