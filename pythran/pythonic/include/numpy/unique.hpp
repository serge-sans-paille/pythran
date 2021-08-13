#ifndef PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  types::ndarray<typename E::dtype, types::pshape<long>> unique(E const &expr);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index);

  template <class E>
  types::ndarray<typename E::dtype, types::pshape<long>>
  unique(E const &expr, std::false_type return_index);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::false_type return_index, std::true_type return_inverse);

  template <class E>
  types::ndarray<typename E::dtype, types::pshape<long>>
  unique(E const &expr, std::false_type return_index, std::false_type return_inverse);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::false_type return_inverse);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::true_type return_inverse);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::true_type return_inverse,
         std::true_type return_counts);
  
  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::true_type return_inverse,
         std::false_type return_counts);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::false_type return_inverse,
         std::false_type return_counts);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::true_type return_index, std::false_type return_inverse,
         std::true_type return_counts);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::false_type return_index, std::true_type return_inverse,
         std::false_type return_counts);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::false_type return_index, std::true_type return_inverse,
         std::true_type return_counts);

  template <class E>
  types::ndarray<typename E::dtype, types::pshape<long>> 
  unique(E const &expr, std::false_type return_index, std::false_type return_inverse,
         std::false_type return_counts);

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, std::false_type return_index, std::false_type return_inverse,
         std::true_type return_counts);

  DEFINE_FUNCTOR(pythonic::numpy, unique)
}
PYTHONIC_NS_END

#endif
