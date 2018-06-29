#ifndef PYTHONIC_INCLUDE_NUMPY_CONCATENATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONCATENATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E, size_t M>
  auto concatenate(types::array<E, M> const &args, long axis = 0)
      -> decltype(asarray(std::get<0>(args)));

  template <class... Types>
  auto concatenate(std::tuple<Types...> const &args, long axis = 0)
      -> types::ndarray<
          typename __combined<typename std::decay<Types>::type::dtype...>::type,
          types::array<
              long, std::tuple_element<0, std::tuple<Types...>>::type::value>>;

  template <class E>
  auto concatenate(types::list<E> const &args, long axis = 0)
      -> decltype(asarray(std::get<0>(args)));

  DECLARE_FUNCTOR(pythonic::numpy, concatenate);
}
PYTHONIC_NS_END

#endif
