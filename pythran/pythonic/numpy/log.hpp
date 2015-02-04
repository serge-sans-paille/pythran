#ifndef PYTHONIC_NUMPY_LOG_HPP
#define PYTHONIC_NUMPY_LOG_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/log.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME log
#define NUMPY_NARY_FUNC_SYM nt2::log
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

