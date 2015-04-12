""" Module to test slice implementation. """

import numpy

from test_env import TestEnv


class TestSlice(TestEnv):

    """
    Unittest class for code using slices.

    We skip tests for None step as it is equivalent to 1.

    TODO : add tests for 1 == step (None as step)
    """

    def test_slice_combination1(self):
        """ Check for "all none" combination. """
        code = """
def slice_combination1(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::-4][begin:end:step],
            a[::4][begin:end:step],
            a[87::-4][begin:end:step],
            a[1::4][begin:end:step],
            a[-3::-4][begin:end:step],
            a[-89::4][begin:end:step],
            a[88:1:-4][begin:end:step],
            a[1:88:4][begin:end:step],
            a[-2:1:-4][begin:end:step],
            a[-89:88:4][begin:end:step],
            a[88:-88:-4][begin:end:step],
            a[2:-1:4][begin:end:step],
            a[-1:-88:-4][begin:end:step],
            a[-88:-1:4][begin:end:step],
            a[:1:-4][begin:end:step],
            a[:87:4][begin:end:step],
            a[:-87:-4][begin:end:step],
            a[:-3:4][begin:end:step])
        """.format(begin=None, end=None, step=None)
        self.run_test(code, numpy.arange(90),
                      slice_combination1=[numpy.array([int])])

    def test_slice_combination2(self):
        """ Check for positive step combination. """
        code = """
def slice_combination2(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::-4][begin:end:step],
            a[::4][begin:end:step],
            a[87::-4][begin:end:step],
            a[1::4][begin:end:step],
            a[-3::-4][begin:end:step],
            a[-89::4][begin:end:step],
            a[88:1:-4][begin:end:step],
            a[1:88:4][begin:end:step],
            a[-2:1:-4][begin:end:step],
            a[-89:88:4][begin:end:step],
            a[88:-88:-4][begin:end:step],
            a[2:-1:4][begin:end:step],
            a[-1:-88:-4][begin:end:step],
            a[-88:-1:4][begin:end:step],
            a[:1:-4][begin:end:step],
            a[:87:4][begin:end:step],
            a[:-87:-4][begin:end:step],
            a[:-3:4][begin:end:step])
        """.format(begin=None, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination2=[numpy.array([int])])

    def test_slice_combination3(self):
        """ Check for negative step combination. """
        code = """
def slice_combination3(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step])
# Reversing values with not continuous step is not implemented
#            a[::-4][begin:end:step],
#            a[::4][begin:end:step],
#            a[87::-4][begin:end:step],
#            a[1::4][begin:end:step],
#            a[-3::-4][begin:end:step],
#            a[-89::4][begin:end:step],
#            a[88:1:-4][begin:end:step],
#            a[1:88:4][begin:end:step],
#            a[-2:1:-4][begin:end:step],
#            a[-89:88:4][begin:end:step],
#            a[88:-88:-4][begin:end:step],
#            a[2:-1:4][begin:end:step],
#            a[-1:-88:-4][begin:end:step],
#            a[-88:-1:4][begin:end:step],
#            a[:1:-4][begin:end:step],
#            a[:87:4][begin:end:step],
#            a[:-87:-4][begin:end:step],
#            a[:-3:4][begin:end:step])
        """.format(begin=None, end=None, step=-2)
        self.run_test(code, numpy.arange(90),
                      slice_combination3=[numpy.array([int])])

    def test_slice_combination4(self):
        """ Check for pos step/no begin/pos end combination. """
        code = """
def slice_combination4(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::4][begin:end:step],
            a[87::-4][begin:end:step],
            a[1::4][begin:end:step],
            a[-3::-4][begin:end:step],
            a[-89::4][begin:end:step],
            a[88:1:-4][begin:end:step],
            a[1:88:4][begin:end:step],
            a[-2:1:-4][begin:end:step],
            a[-89:88:4][begin:end:step],
            a[88:-88:-4][begin:end:step],
            a[2:-1:4][begin:end:step],
            a[-1:-88:-4][begin:end:step],
            a[-88:-1:4][begin:end:step],
            a[:1:-4][begin:end:step],
            a[:87:4][begin:end:step],
            a[:-87:-4][begin:end:step],
            a[:-3:4][begin:end:step])
        """.format(begin=None, end=7, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination4=[numpy.array([int])])

    def test_slice_combination5(self):
        """ Check for pos step/no begin/neg end combination. """
        code = """
def slice_combination5(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step])
# Not implementer for negative end
#            a[::4][begin:end:step],
#            a[87::-4][begin:end:step],
#            a[1::4][begin:end:step],
#            a[-3::-4][begin:end:step],
#            a[-89::4][begin:end:step],
#            a[88:1:-4][begin:end:step],
#            a[1:88:4][begin:end:step],
#            a[-2:1:-4][begin:end:step],
#            a[-89:88:4][begin:end:step],
#            a[88:-88:-4][begin:end:step],
#            a[2:-1:4][begin:end:step],
#            a[-1:-88:-4][begin:end:step],
#            a[-88:-1:4][begin:end:step],
#            a[:1:-4][begin:end:step],
#            a[:87:4][begin:end:step],
#            a[:-87:-4][begin:end:step],
#            a[:-3:4][begin:end:step])
        """.format(begin=None, end=-3, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination5=[numpy.array([int])])

    def test_slice_combination6(self):
        """ Check for pos step/pos begin/no end combination. """
        code = """
def slice_combination6(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::4][begin:end:step],
            a[87::-4][begin:end:step],
            a[1::4][begin:end:step],
            a[-3::-4][begin:end:step],
            a[-89::4][begin:end:step],
            a[88:1:-4][begin:end:step],
            a[1:88:4][begin:end:step],
            a[-2:1:-4][begin:end:step],
            a[-89:88:4][begin:end:step],
            a[88:-88:-4][begin:end:step],
            a[2:-1:4][begin:end:step],
            a[-1:-88:-4][begin:end:step],
            a[-88:-1:4][begin:end:step],
            a[:1:-4][begin:end:step],
            a[:87:4][begin:end:step],
            a[:-87:-4][begin:end:step],
            a[:-3:4][begin:end:step])
        """.format(begin=2, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination6=[numpy.array([int])])

    def test_slice_combination7(self):
        """ Check for pos step/pos begin/pos end combination. """
        code = """
def slice_combination7(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::4][begin:end:step],
            a[87::-4][begin:end:step],
            a[1::4][begin:end:step],
            a[-3::-4][begin:end:step],
            a[-89::4][begin:end:step],
            a[88:1:-4][begin:end:step],
            a[1:88:4][begin:end:step],
            a[-2:1:-4][begin:end:step],
            a[-89:88:4][begin:end:step],
            a[88:-88:-4][begin:end:step],
            a[2:-1:4][begin:end:step],
            a[-1:-88:-4][begin:end:step],
            a[-88:-1:4][begin:end:step],
            a[:1:-4][begin:end:step],
            a[:87:4][begin:end:step],
            a[:-87:-4][begin:end:step],
            a[:-3:4][begin:end:step])
        """.format(begin=2, end=9, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination7=[numpy.array([int])])

    def test_slice_combination8(self):
        """ Check for pos step/neg begin/no end combination. """
        code = """
def slice_combination8(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step])
# Not implementer for negative begin
#            a[::4][begin:end:step],
#            a[87::-4][begin:end:step],
#            a[1::4][begin:end:step],
#            a[-3::-4][begin:end:step],
#            a[-89::4][begin:end:step],
#            a[88:1:-4][begin:end:step],
#            a[1:88:4][begin:end:step],
#            a[-2:1:-4][begin:end:step],
#            a[-89:88:4][begin:end:step],
#            a[88:-88:-4][begin:end:step],
#            a[2:-1:4][begin:end:step],
#            a[-1:-88:-4][begin:end:step],
#            a[-88:-1:4][begin:end:step],
#            a[:1:-4][begin:end:step],
#            a[:87:4][begin:end:step],
#            a[:-87:-4][begin:end:step],
#            a[:-3:4][begin:end:step])
        """.format(begin=-10, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      slice_combination8=[numpy.array([int])])

    def test_step1slice_combination1(self):
        """ Check for "all none" combination. """
        code = """
def step1slice_combination1(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::-1][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=None, step=None)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination1=[numpy.array([int])])

    def test_step1slice_combination2(self):
        """ Check for positive step combination. """
        code = """
def step1slice_combination2(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::-1][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination2=[numpy.array([int])])

    def test_step1slice_combination3(self):
        """ Check for negative step combination. """
        code = """
def step1slice_combination3(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::-1][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-2:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=None, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination3=[numpy.array([int])])

    def test_step1slice_combination4(self):
        """ Check for pos step/no begin/pos end combination. """
        code = """
def step1slice_combination4(a):
    begin = {begin}
    end = {end}
    step = {step}
    return(a[::][begin:end:step],
           a[::1][begin:end:step],
           a[87::-1][begin:end:step],
           a[1::1][begin:end:step],
           a[-3::-1][begin:end:step],
           a[-89::1][begin:end:step],
           a[88:1:-1][begin:end:step],
           a[1:88:1][begin:end:step],
           a[-2:1:-1][begin:end:step],
           a[-89:88:1][begin:end:step],
           a[88:-88:-1][begin:end:step],
           a[2:-1:1][begin:end:step],
           a[-1:-88:-1][begin:end:step],
           a[-88:-1:1][begin:end:step],
           a[:1:-1][begin:end:step],
           a[:87:1][begin:end:step],
           a[:-87:-1][begin:end:step],
           a[:-3:1][begin:end:step])
        """.format(begin=None, end=7, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination4=[numpy.array([int])])

    def test_step1slice_combination5(self):
        """ Check for pos step/no begin/neg end combination. """
        code = """
def step1slice_combination5(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=-3, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination5=[numpy.array([int])])

    def test_step1slice_combination6(self):
        """ Check for pos step/pos begin/no end combination. """
        code = """
def step1slice_combination6(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=2, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination6=[numpy.array([int])])

    def test_step1slice_combination7(self):
        """ Check for pos step/pos begin/pos end combination. """
        code = """
def step1slice_combination7(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=2, end=9, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination7=[numpy.array([int])])

    def test_step1slice_combination8(self):
        """ Check for pos step/neg begin/no end combination. """
        code = """
def step1slice_combination8(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-10, end=None, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination8=[numpy.array([int])])

    def test_step1slice_combination9(self):
        """ Check for neg step/no begin/pos end combination. """
        code = """
def step1slice_combination9(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=2, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination9=[numpy.array([int])])

    def test_step1slice_combination10(self):
        """ Check for neg step/no begin/neg end combination. """
        code = """
def step1slice_combination10(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=None, end=-10, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination10=[numpy.array([int])])

    def test_step1slice_combination11(self):
        """ Check for neg step/pos begin/neg end combination. """
        code = """
def step1slice_combination11(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=85, end=-10, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination11=[numpy.array([int])])

    def test_step1slice_combination12(self):
        """ Check for neg step/pos begin/no end combination. """
        code = """
def step1slice_combination12(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=85, end=None, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination12=[numpy.array([int])])

    def test_step1slice_combination13(self):
        """ Check for neg step/pos begin/pos end combination. """
        code = """
def step1slice_combination13(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=85, end=3, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination13=[numpy.array([int])])

    def test_step1slice_combination14(self):
        """ Check for pos step/neg begin/no end combination. """
        code = """
def step1slice_combination14(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-3, end=None, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination14=[numpy.array([int])])

    def test_step1slice_combination15(self):
        """ Check for neg step/neg begin/pos end combination. """
        code = """
def step1slice_combination15(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-3, end=4, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination15=[numpy.array([int])])

    def test_step1slice_combination16(self):
        """ Check for neg step/neg begin/neg end combination. """
        code = """
def step1slice_combination16(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-3, end=-10, step=-2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination16=[numpy.array([int])])

    def test_step1slice_combination17(self):
        """ Check for pos step/pos begin/neg end combination. """
        code = """
def step1slice_combination17(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=3, end=-10, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination17=[numpy.array([int])])

    def test_step1slice_combination18(self):
        """ Check for pos step/pos begin/neg end combination. """
        code = """
def step1slice_combination18(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-80, end=80, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination18=[numpy.array([int])])

    def test_step1slice_combination19(self):
        """ Check for pos step/neg begin/neg end combination. """
        code = """
def step1slice_combination19(a):
    begin = {begin}
    end = {end}
    step = {step}
    return (a[::][begin:end:step],
            a[::1][begin:end:step],
            a[87::-1][begin:end:step],
            a[1::1][begin:end:step],
            a[-3::-1][begin:end:step],
            a[-89::1][begin:end:step],
            a[88:1:-1][begin:end:step],
            a[1:88:1][begin:end:step],
            a[-2:1:-1][begin:end:step],
            a[-89:88:1][begin:end:step],
            a[88:-88:-1][begin:end:step],
            a[2:-1:1][begin:end:step],
            a[-1:-88:-1][begin:end:step],
            a[-88:-1:1][begin:end:step],
            a[:1:-1][begin:end:step],
            a[:87:1][begin:end:step],
            a[:-87:-1][begin:end:step],
            a[:-3:1][begin:end:step])
        """.format(begin=-80, end=-2, step=2)
        self.run_test(code, numpy.arange(90),
                      step1slice_combination19=[numpy.array([int])])
