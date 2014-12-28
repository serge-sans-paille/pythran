#ifndef PYTHONIC_NUMPY_CUMPROD_HPP
#define PYTHONIC_NUMPY_CUMPROD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/partial_sum.hpp"

namespace pythonic {

    namespace numpy {

        template<class E, class... Opts>
          auto cumprod(E&& e, Opts&&... opts) -> decltype(partial_sum<operator_::proxy::imul>(std::forward<E>(e), std::forward<Opts>(opts)...)) {
            return partial_sum<operator_::proxy::imul>(std::forward<E>(e), std::forward<Opts>(opts)...);
          }

        NUMPY_EXPR_TO_NDARRAY0(cumprod);

        PROXY(pythonic::numpy, cumprod);

    }

}

#endif

