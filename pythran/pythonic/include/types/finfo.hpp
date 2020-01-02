#ifndef PYTHONIC_INCLUDE_TYPES_FINFO_HPP
#define PYTHONIC_INCLUDE_TYPES_FINFO_HPP

#include "pythonic/include/types/attr.hpp"

#include <limits>

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  struct finfo {
    T eps() const;
  };
}
PYTHONIC_NS_END

/* pythran attribute system { */
PYTHONIC_NS_BEGIN
namespace builtins
{
  template <class T>
  T getattr(pythonic::types::finfo<T> const &f,
            std::integral_constant<size_t, types::attr::EPS>);
}
PYTHONIC_NS_END
/* } */
#endif
