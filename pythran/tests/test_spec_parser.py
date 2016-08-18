import unittest
import pythran
import os.path

#pythran export a((float,(int,long),str list) list list)
#pythran export a(str)
#pythran export a( (str,str), int, long list list)
#pythran export a( long set )
#pythran export a( long:str dict )
#pythran export a( long )
#pythran export a( long[] )
#pythran export a( long[][] )
#pythran export a( int8 )
#pythran export a( uint8 )
#pythran export a( int16 )
#pythran export a( uint16 )
#pythran export a( int32 )
#pythran export a( uint32 )
#pythran export a( int64 )
#pythran export a( uint64 )
#pythran export a( float32 )
#pythran export a( float64 )
#pythran export a( complex64 )
#pythran export a( complex128 )
#pythran export a( int8 set )
#pythran export a( uint8 list)
#pythran export a( int16 [])
#pythran export a( uint16 [][])
#pythran export a( uint16 [::][])
#pythran export a( uint16 [:,:,:])
#pythran export a( uint16 [:,::,:])
#pythran export a( uint16 [,,])
#pythran export a( (int32, ( uint32 , int64 ) ) )
#pythran export a( uint64:float32 dict )
#pythran export a( float64, complex64, complex128 )

class TestSpecParser(unittest.TestCase):

    def test_parser(self):
        real_path = os.path.splitext(os.path.realpath(__file__))[0]+".py"
        print(pythran.spec_parser(real_path))

    def test_invalid_specs0(self):
        code = '#pythran export foo()\ndef foo(n): return n'
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            pythran.compile_pythrancode("dumber", code)

    def test_invalid_specs1(self):
        code = '#pythran export foo(int)\ndef foo(): pass'
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            pythran.compile_pythrancode("dumber", code)

    def test_invalid_specs2(self):
        code = '#pythran export bar(int)\ndef foo(): pass'
        with self.assertRaises(pythran.syntax.PythranSyntaxError):
            pythran.compile_pythrancode("dumber", code)

    def test_multiline_spec0(self):
        code = '''
#pythran export foo(
              # )
def foo(): return
            '''
        self.assertTrue(pythran.spec_parser(code))

    def test_multiline_spec1(self):
        code = '''
#pythran export foo(int
  #, int
              # )
def foo(i,j): return
            '''
        self.assertTrue(pythran.spec_parser(code))

    def test_multiline_spec2(self):
        code = '''
#      pythran export foo(int,

# float
  #, int
              # )
def foo(i,j,k): return
            '''
        self.assertTrue(pythran.spec_parser(code))

    def test_crappy_spec0(self):
        code = '''
#      pythran export foo(int) this is an int test
def foo(i): return
            '''
        self.assertTrue(pythran.spec_parser(code))

    def test_crappy_spec1(self):
        code = '''
#      pythran export foo(int)
#this is a pythran export test
def foo(i): return
            '''
        self.assertTrue(pythran.spec_parser(code))

    def test_middle_spec0(self):
        code = '''
def foo(i): return
#      pythran export foo(int)
#this is a pythran export test
def bar(i): return
            '''
        self.assertTrue(pythran.spec_parser(code))


    def test_middle_spec1(self):
        code = '''
def foo(i): return
#this is a pythran export test
#      pythran export foo(int)
#this is an export test
#      pythran export foo(float)
def bar(i): return
            '''
        self.assertEquals(len(pythran.spec_parser(code)), 1)
        self.assertEquals(len(pythran.spec_parser(code)['foo']), 2)

    def test_var_export0(self):
        code = '''
#      pythran export foo
foo = 1
            '''
        self.assertTrue(pythran.spec_parser(code))
