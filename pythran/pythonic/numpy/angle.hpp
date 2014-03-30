#ifndef PYTHONIC_NUMPY_ANGLE_HPP
#define PYTHONIC_NUMPY_ANGLE_HPP

#include "pythonic/numpy/angle_in_deg.hpp"
#include "pythonic/numpy/angle_in_rad.hpp"
#include "pythonic/types/assignable.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto angle(T const& t, bool in_deg = false)
            -> typename assignable<decltype(proxy::angle_in_rad()(t))>::type
            // assignable to find a common type between the two expression templaes
            {
                if(in_deg)
                    return proxy::angle_in_deg()(t);
                else
                    return proxy::angle_in_rad()(t);
            }
        PROXY(pythonic::numpy, angle);

    }

}

#endif

