#ifndef PYTHONIC_TYPES_FINFO_HPP
#define PYTHONIC_TYPES_FINFO_HPP

#include "pythonic/include/types/finfo.hpp"

#include "pythonic/types/attr.hpp"

#include <limits>

namespace pythonic
{

  namespace types
  {
    template <class T>
    T finfo<T>::eps() const
    {
      return std::numeric_limits<T>::epsilon();
    }
  }
}

/* pythran attribute system { */
namespace pythonic
{
  namespace types
  {
    namespace __finfo
    {

      template <class T>
      auto getattr<attr::EPS, T>::operator()(finfo<T> const &f)
          -> decltype(f.eps()) const
      {
        return f.eps();
      }
    }
  }
  namespace __builtin__
  {
    template <int I, class T>
    auto getattr(pythonic::types::finfo<T> const &f)
        -> decltype(pythonic::types::__finfo::getattr<I, T>()(f))
    {
      return pythonic::types::__finfo::getattr<I, T>()(f);
    }
  }
}
/* } */
#endif
