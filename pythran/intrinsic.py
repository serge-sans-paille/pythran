class Intrinsic:
    def __init__(self):
        pass

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

class FunctionIntr(Intrinsic):
    def __init__(self):
        pass

    def isfunction(self):
        return True

    def isstaticfunction(self):
        return True

class MethodIntr(FunctionIntr):
    def __init__(self,_combiner = []):
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
