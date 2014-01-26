#ifndef PYTHONIC_BUILTIN_STR_HPP
#define PYTHONIC_BUILTIN_STR_HPP

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

#include <sstream>

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            types::str str(T&& t) {
                std::ostringstream oss;
                oss << t;
                return oss.str();
            }

        types::str str(long value) {
            /* adapted from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html#performance */
            thread_local static char buffer[8*(1 << sizeof(value))]; // this buffer is large enough to hold the binary representation, so the decimal representation will be ok 
            char* ptr = buffer, *ptr1 = buffer, tmp_char;
            long tmp_value;

            do {
                tmp_value = value;
                value /= 10;
                *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * 10)];
            } while ( value );

            // Apply negative sign
            if (tmp_value < 0) *ptr++ = '-';
            *ptr-- = '\0';
            while(ptr1 < ptr) {
                tmp_char = *ptr;
                *ptr--= *ptr1;
                *ptr1++ = tmp_char;
            }
            return buffer;
        }

        types::str str(double l) {
            thread_local static char buffer[8*(1 << sizeof(l))]; // when using %g, only 6 significant bits are used, so this should be enough. Use snprintf though
            snprintf(buffer, sizeof(buffer), "%g", l);
            return buffer;
        }

        PROXY(pythonic::__builtin__, str);

    }

}

#endif
