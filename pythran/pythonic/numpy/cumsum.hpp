#ifndef PYTHONIC_NUMPY_CUMSUM_HPP
#define PYTHONIC_NUMPY_CUMSUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/partial_sum.hpp"

namespace pythonic {

    namespace numpy {

        template<class E, class... Opts>
          auto cumsum(E&& e, Opts&&... opts) -> decltype(partial_sum<operator_::proxy::iadd>(std::forward<E>(e), std::forward<Opts>(opts)...)) {
            return partial_sum<operator_::proxy::iadd>(std::forward<E>(e), std::forward<Opts>(opts)...);
          }

        PROXY(pythonic::numpy, cumsum);

    }

}

#endif

