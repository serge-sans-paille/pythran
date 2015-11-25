#ifndef PYTHONIC_INCLUDE_NUMPY_LINALG_NORM_HPP
#define PYTHONIC_INCLUDE_NUMPY_LINALG_NORM_HPP

#include "pythonic/include/numpy/abs.hpp"
#include "pythonic/include/numpy/sqrt.hpp"
#include "pythonic/include/numpy/square.hpp"
#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/numpy/asfarray.hpp"

namespace pythonic
{
  namespace numpy
  {
    namespace linalg
    {
      template <class Array>
      auto norm(Array &&array, types::none_type ord = {},
                types::none_type axis = {})
          -> decltype(
              pythonic::numpy::functor::sqrt{}(pythonic::numpy::functor::sum{}(
                  pythonic::numpy::functor::square{}(
                      pythonic::numpy::functor::abs{}(
                          pythonic::numpy::functor::asfarray{}(
                              std::forward<Array>(array)))))));

      template <class Array>
      using norm_dtype_t = typename std::conditional<
          std::is_floating_point<
              typename std::decay<Array>::type::dtype()>::value,
          typename std::decay<Array>::type::dtype(), double>::type;

      template <class Array>
      using norm_t = typename std::conditional<
          std::decay<Array>::type::value == 1, norm_dtype_t<Array>,
          types::ndarray<norm_dtype_t<Array>,
                         std::decay<Array>::type::value - 1>>::type;

      template <class Array>
      norm_t<Array> norm(Array &&array, double ord, types::none_type axis = {});

      template <class Array>
      norm_t<Array> norm(Array &&array, types::none_type ord, double axis);

      template <class Array>
      norm_t<Array> norm(Array &&array, double ord, long axis);

      template <class Array>
      norm_t<Array> norm(Array &&array, double ord, types::array<long, 1> axis);

      template <class Array>
      norm_t<Array> norm(Array &&array, double ord, types::array<long, 2> axis);
      DECLARE_FUNCTOR(pythonic::numpy::linalg, norm);
    }
  }
}

#endif
