from test_env import TestEnv
import numpy

class TestNumpy(TestEnv):

    def test_array1D_(self):
        self.run_test("def array1D_():\n from numpy import array\n return array([1,2,3])", array1D_=[])
        
    def test_array2D_(self):
        self.run_test("def array2D_():\n from numpy import array\n return array([[1,2],[3,4]])", array2D_=[])

    def test_arrayND_(self):
        self.run_test("def arrayND_():\n from numpy import array\n return array([[i,j,k,l] for i in xrange(5) for j in xrange(4) for k in xrange(6) for l in xrange(8)])", arrayND_=[])

    def test_zeros_(self):
        self.run_test("def zeros_():\n from numpy import zeros\n return zeros((10,5))", zeros_=[])

    def test_ones_(self):
        self.run_test("def ones_():\n from numpy import zeros\n return zeros((10,5))", ones_=[])

    def test_acces1D_(self):
        self.run_test("def acces1D_():\n from numpy import array\n a =array([1,2,3])\n return a[1]", acces1D_=[])

    def test_accesSimple_(self):
        self.run_test("def accesSimple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1]", accesSimple_=[])

    def test_accesMultiple_(self):
        self.run_test("def accesMultiple_():\n from numpy import array\n a =array([[1,2],[3,4]])\n return a[1,0]", accesMultiple_=[])

    def test_accesMultipleND_(self):
        self.run_test("def accesMultipleND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1,0]", accesMultipleND_=[])

    def test_accesMultipleNDSplit_(self):
        self.run_test("def accesMultipleNDSplit_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a[1][0]", accesMultipleNDSplit_=[])

    def test_shape_(self):
        self.run_test("def shape_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.shape", shape_=[])

    def test_input_array_(self):
        self.run_test("import numpy\n\ndef input_array_(a):\n return a.shape", numpy.array([[1,2],[3,4]]), input_array_=[numpy.array([[int]])])

    def test_change_array1D_(self):
        self.run_test("\n\ndef change_array1D_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0,0] = 36\n return a", change_array1D_=[])

    def test_change_arrayND_(self):
        self.run_test("\n\ndef change_arrayND_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n a[0,0] = array([99,99])\n return a", change_arrayND_=[])

    def test_ndim_(self):
        self.run_test("\n\ndef ndim_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.ndim", ndim_=[])

    def test_stride_(self):
        self.run_test("\n\ndef stride_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.strides", stride_=[])

    def test_size_(self):
        self.run_test("\n\ndef size_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.size", size_=[])

    def test_itemsize_(self):
        self.run_test("\n\ndef itemsize_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.itemsize", itemsize_=[])

    def test_nbytes_(self):
        self.run_test("\n\ndef nbytes_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return a.nbytes", nbytes_=[])

    def test_flat_(self):
        self.run_test("\n\ndef flat_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return [i for i in a.flat]", flat_=[])

    def test_str_(self):
        self.run_test("\n\ndef str_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return str(a)", str_=[])

    def test_len_(self):
        self.run_test("\n\ndef len_():\n from numpy import array\n a =array([[[1,2],[3,4]],[[5,6],[7,8]]])\n return len(a)", len_=[])
