#ifndef PYTHONIC_NUMPY_MIN_HPP
#define PYTHONIC_NUMPY_MIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/reduce.hpp"

namespace pythonic {

    namespace numpy {

        template<class E>
          auto min(E&& e) -> decltype(reduce<operator_::proxy::imin>(std::forward<E>(e))) {
            return reduce<operator_::proxy::imin>(std::forward<E>(e));
          }
        template<class E, class Opt>
          auto min(E&& e, Opt&& opt) -> decltype(reduce<operator_::proxy::imin>(std::forward<E>(e), std::forward<Opt>(opt))) {
            return reduce<operator_::proxy::imin>(std::forward<E>(e), std::forward<Opt>(opt));
          }

        PROXY(pythonic::numpy, min);

    }

}

#endif

