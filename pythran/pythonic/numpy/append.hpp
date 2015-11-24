#ifndef PYTHONIC_NUMPY_APPEND_HPP
#define PYTHONIC_NUMPY_APPEND_HPP

#include "pythonic/include/numpy/append.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N, class F>
    types::ndarray<
        typename std::remove_cv<typename std::remove_reference<
            decltype(std::declval<T>() +
                     std::declval<typename utils::nested_container_value_type<
                         F>::type>())>::type>::type,
        1>
    append(types::ndarray<T, N> const &nto, F const &data)
    {
      types::ndarray<typename F::dtype, F::value> ndata(data);
      long nsize = nto.flat_size() + ndata.flat_size();
      types::ndarray<
          typename std::remove_cv<typename std::remove_reference<decltype(
              std::declval<T>() +
              std::declval<typename utils::nested_container_value_type<
                  F>::type>())>::type>::type,
          1> out(types::make_tuple(nsize), __builtin__::None);
      auto out_back = std::copy(nto.fbegin(), nto.fend(), out.fbegin());
      std::copy(ndata.fbegin(), ndata.fend(), out_back);
      return out;
    }

    template <class T, class F>
    types::ndarray<
        typename std::remove_cv<typename std::remove_reference<
            decltype(std::declval<typename utils::nested_container_value_type<
                         types::list<T>>::type>() +
                     std::declval<typename utils::nested_container_value_type<
                         F>::type>())>::type>::type,
        1>
    append(types::list<T> const &to, F const &data)
    {
      return append(
          types::ndarray<typename types::list<T>::dtype, types::list<T>::value>(
              to),
          data);
    }

    DEFINE_FUNCTOR(pythonic::numpy, append);
  }
}

#endif
