import unittest
from pythran import spec_parser
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
#pythran export a( (int32, ( uint32 , int64 ) ) )
#pythran export a( uint64:float32 dict )
#pythran export a( float64, complex64, complex128 )

class TestSpecParser(unittest.TestCase):

    def test_parser(self):
        real_path = os.path.splitext(os.path.realpath(__file__))[0]+".py"
        print spec_parser(real_path)
