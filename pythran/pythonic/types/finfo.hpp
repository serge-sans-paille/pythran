#ifndef PYTHONIC_TYPES_FINFO_HPP
#define PYTHONIC_TYPES_FINFO_HPP

#include "pythonic/include/types/finfo.hpp"

#include "pythonic/types/attr.hpp"

#include <limits>

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  T finfo<T>::eps() const
  {
    return std::numeric_limits<T>::epsilon();
  }
}
PYTHONIC_NS_END

/* pythran attribute system { */
PYTHONIC_NS_BEGIN
namespace builtins
{
  template <class T>
  T getattr(pythonic::types::finfo<T> const &f,
            std::integral_constant<size_t, types::attr::EPS>)
  {
    return f.eps();
  }
}
PYTHONIC_NS_END
/* } */
#endif
