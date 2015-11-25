#ifndef PYTHONIC_INCLUDE_NUMPY_INSERT_HPP
#define PYTHONIC_INCLUDE_NUMPY_INSERT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/__builtin__/None.hpp"

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {

    template <class T, size_t N, class I, class F>
    typename std::enable_if<types::is_iterable<I>::value and
                                types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis = __builtin__::None);

    template <class T, size_t N, class I, class F>
    typename std::enable_if<types::is_iterable<I>::value and
                                not types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis = __builtin__::None);

    template <class T, size_t N, class I, class F>
    typename std::enable_if<not types::is_iterable<I>::value and
                                types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis = __builtin__::None);

    template <class T, size_t N, class I, class F>
    typename std::enable_if<not types::is_iterable<I>::value and
                                not types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis = __builtin__::None);

    template <class E, class... Args>
    E insert(E, Args const &...);

    DECLARE_FUNCTOR(pythonic::numpy, insert);
  }
}

#endif
