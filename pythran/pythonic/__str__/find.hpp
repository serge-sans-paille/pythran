#ifndef PYTHONIC_STR_FIND_HPP
#define PYTHONIC_STR_FIND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {

        long find(types::str const & s, types::str const& value, size_t start, long long end) {
            long a = s.find(value,start);
            return (a>end)?-1:a;
        }
        long find(types::str const & s, types::str const& value, size_t start) {
            return find(s,value,start,s.size());
        }
        long find(types::str const & s, types::str const& value) {
            return find(s,value,0,s.size());
        }
        PROXY(pythonic::__str__, find);
    }

}

#endif

