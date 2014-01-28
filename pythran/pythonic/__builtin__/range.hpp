#ifndef PYTHONIC_BUILTIN_RANGE_HPP
#define PYTHONIC_BUILTIN_RANGE_HPP

#include "pythonic/__builtin__/xrange.hpp"
#include "pythonic/__builtin__/len.hpp"

#include "pythonic/types/list.hpp"

#include "pythonic/utils/fwd.hpp"

namespace pythonic {

    namespace __builtin__ {

        types::list<long> _range(xrange & xr) {
            types::list<long> s(len(xr));
            std::copy(xr.begin(), xr.end(), s.begin());
            return s;
        }

        types::list<long> range(long e) {
            xrange xr(e);
            return _range(xr);
        }
        types::list<long> range(long b, long e, long s=1) {
            xrange xr(b, e, s);
            return _range(xr);
        }
        PROXY(pythonic::__builtin__,range);

    }

}

#endif
