#ifndef PYTHONIC_INCLUDE_TYPES_NUMPYTYPE_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPYTYPE_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace types
  {

    template <class T, typename EnableDefault = void>
    struct numpy_type {
      using type = decltype(std::declval<T>()());
    };

    template <class T>
    struct numpy_type<
        T, typename std::enable_if<std::is_fundamental<T>::value>::type> {
      using type = T;
    };

#define SPECIALIZE_NUMPY_TYPE(TYPE)                                            \
  template <>                                                                  \
  struct numpy_type<TYPE> {                                                    \
    using type = TYPE;                                                         \
  }

    SPECIALIZE_NUMPY_TYPE(std::complex<float>);
    SPECIALIZE_NUMPY_TYPE(std::complex<double>);
#undef SPECIALIZE_NUMPY_TYPE
  }
}

#endif
