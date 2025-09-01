#ifndef PYTHONIC_UTILS_NUMPY_CONVERSION_HPP
#define PYTHONIC_UTILS_NUMPY_CONVERSION_HPP

#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#if _MSC_VER && !__clang__
#define NUMPY_EXPR_TO_NDARRAY0_IMPL(fname)                                     \
  template <class E, class... Types,                                           \
            std::enable_if_t<!types::is_ndarray<E>::value &&                   \
                                        types::is_numexpr_arg<E>::value,       \
                                    E> * = nullptr>                            \
  auto fname(E const &expr, Types &&...others)                                 \
  {                                                                            \
    return fname(types::ndarray<typename E::dtype, typename E::shape_t>{expr}, \
                 std::forward<Types>(others)...);                              \
  }
#else
#define NUMPY_EXPR_TO_NDARRAY0_IMPL(fname)                                     \
  template <class E, class... Types>                                           \
  auto fname(E const &expr, Types &&...others) ->                              \
      std::enable_if_t<                                                        \
          !types::is_ndarray<E>::value && types::is_numexpr_arg<E>::value,     \
          decltype(fname(                                                      \
              types::ndarray<typename E::dtype, typename E::shape_t>{expr},    \
              std::forward<Types>(others)...))>                                \
  {                                                                            \
    return fname(types::ndarray<typename E::dtype, typename E::shape_t>{expr}, \
                 std::forward<Types>(others)...);                              \
  }
#endif
#endif
