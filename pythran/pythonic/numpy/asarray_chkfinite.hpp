#ifndef PYTHONIC_NUMPY_ASARRAYCHKFINITE_HPP
#define PYTHONIC_NUMPY_ASARRAYCHKFINITE_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class... Types>
            auto asarray_chkfinite(Types&&... args) -> decltype(asarray(std::forward<Types>(args)...)) {
                auto out = asarray(std::forward<Types>(args)...);
                for(auto iter = out.buffer, end = out.buffer + out.size();
                        iter != end;
                        ++iter)
                {
                    if(not std::isfinite(*iter))
                        throw types::ValueError("array must not contain infs or NaNs");
                }
                return out;
            }

        PROXY(pythonic::numpy, asarray_chkfinite);

    }

}

#endif

