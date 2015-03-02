#ifndef PYTHONIC_NUMPY_BINARYREPR_HPP
#define PYTHONIC_NUMPY_BINARYREPR_HPP

#include "pythonic/numpy/base_repr.hpp"

namespace pythonic {

    namespace numpy {

        namespace {

            char *int2bin(long a, char *buffer, int buf_size) {
                buffer += (buf_size - 1);
                buffer[1]=0;
                for (int i = 0; i < buf_size; ++i) {
                    *buffer-- = (a & 1) + '0';
                    a >>= 1;
                }
                return buffer;
            }
        }

        types::str binary_repr(long number, types::none_type width=__builtin__::None) {
            return base_repr(number,2);
        }

        types::str binary_repr(long number, long width) {
            types::str out = binary_repr(std::abs(number));
            if(number>=0) {
                return base_repr(number, 2, width - out.size());
            }
            else {
                char * mem = new char[width+1];
                int2bin(number, mem, width);
                auto res = types::str(mem);
                delete [] mem;
                return res;
            }
        }

        PROXY(pythonic::numpy, binary_repr);

    }

}

#endif

