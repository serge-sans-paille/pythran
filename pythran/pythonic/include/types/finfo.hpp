#ifndef PYTHONIC_INCLUDE_TYPES_FINFO_HPP
#define PYTHONIC_INCLUDE_TYPES_FINFO_HPP

#include "pythonic/include/types/attr.hpp"

#include <limits>

namespace pythonic
{

  namespace types
  {
    template <class T>
    struct finfo {
      T eps() const;
    };
  }
}

/* pythran attribute system { */
namespace pythonic
{
  namespace types
  {
    namespace __finfo
    {

      template <int I, class T>
      struct getattr;

      template <class T>
      struct getattr<attr::EPS, T> {
        auto operator()(finfo<T> const &f) -> decltype(f.eps()) const;
      };
    }
  }
  namespace __builtin__
  {
    template <int I, class T>
    auto getattr(pythonic::types::finfo<T> const &f)
        -> decltype(pythonic::types::__finfo::getattr<I, T>()(f));
  }
}
/* } */
#endif
