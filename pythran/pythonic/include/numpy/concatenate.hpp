#ifndef PYTHONIC_INCLUDE_NUMPY_CONCATENATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONCATENATE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/sum.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N, size_t M>
    types::ndarray<T, N>
    concatenate(types::array<types::ndarray<T, N>, M> const &ai);

    template <class... Types>
    typename assignable<typename __combined<Types...>::type>::type
    concatenate(std::tuple<Types...> const &args);

    PROXY_DECL(pythonic::numpy, concatenate);
  }
}

#endif
