#ifndef PYTHONIC_NUMPY_BASEREPR_HPP
#define PYTHONIC_NUMPY_BASEREPR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        namespace {
            char* itoa( int value, char* result, int base ) {
                // check that the base if valid
                if (base < 2 || base > 16) { *result = 0; return result; }

                char* out = result;
                int quotient = abs(value);

                do {
                    const int tmp = quotient / base;
                    *out = "0123456789ABCDEF"[ quotient - (tmp*base) ];
                    ++out;
                    quotient = tmp;
                } while ( quotient );

                // Apply negative sign
                if ( value < 0) *out++ = '-';

                std::reverse( result, out );
                *out = 0;
                return result;
            }
        }
        types::str base_repr(long number, long base=2, long padding=0) {
            char * mem = new char[sizeof(number)*8+1 + padding];
            std::fill(mem, mem+padding, '0');
            itoa(number, mem + padding, base);
            auto res = types::str(mem);
            delete [] mem;
            return res;
        }

        PROXY(pythonic::numpy, base_repr);

    }

}

#endif

