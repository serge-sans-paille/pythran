#ifndef PYTHONIC_NUMPY_ATLEAST3D_HPP
#define PYTHONIC_NUMPY_ATLEAST3D_HPP

#include "pythonic/include/numpy/atleast_3d.hpp"

#include "pythonic/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T>
  std::enable_if_t<
      types::is_dtype<T>::value,
      types::ndarray<T, types::pshape<std::integral_constant<long, 1>,
                                      std::integral_constant<long, 1>,
                                      std::integral_constant<long, 1>>>>
  atleast_3d(T t)
  {
    return {types::pshape<std::integral_constant<long, 1>,
                          std::integral_constant<long, 1>,
                          std::integral_constant<long, 1>>(),
            t};
  }

  template <class T>
  auto atleast_3d(T const &t) ->
      std::enable_if_t<
          (!types::is_dtype<T>::value) && (T::value == 1),
          types::ndarray<typename T::dtype,
                         types::pshape<std::integral_constant<long, 1>,
                                       std::tuple_element_t<0, typename T::shape_t>,
                                       std::integral_constant<long, 1>>>>
  {
    auto r = asarray(t);
    return r.reshape(
        types::pshape<std::integral_constant<long, 1>,
                      std::tuple_element_t<0, typename T::shape_t>,
                      std::integral_constant<long, 1>>(
            std::integral_constant<long, 1>(), r.template shape<0>(),
            std::integral_constant<long, 1>()));
  }

  template <class T>
  auto atleast_3d(T const &t) ->
      std::enable_if_t<
          (!types::is_dtype<T>::value) && (T::value == 2),
          types::ndarray<
              typename T::dtype,
              types::pshape<
                  std::tuple_element_t<0, typename T::shape_t>,
                  std::tuple_element_t<1, typename T::shape_t>,
                  std::integral_constant<long, 1>>>>
  {
    auto r = asarray(t);
    return r.reshape(
        types::pshape<std::tuple_element_t<0, typename T::shape_t>,
                      std::tuple_element_t<1, typename T::shape_t>,
                      std::integral_constant<long, 1>>(
            r.template shape<0>(), r.template shape<1>(),
            std::integral_constant<long, 1>()));
  }

  template <class T>
  auto atleast_3d(T const &t) ->
      std::enable_if_t<(!types::is_dtype<T>::value) && T::value >= 3, decltype(asarray(t))>
  {
    return asarray(t);
  }
} // namespace numpy
PYTHONIC_NS_END

#endif
