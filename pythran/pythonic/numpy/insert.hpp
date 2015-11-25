#ifndef PYTHONIC_NUMPY_INSERT_HPP
#define PYTHONIC_NUMPY_INSERT_HPP

#include "pythonic/include/numpy/insert.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/__builtin__/None.hpp"

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
           types::none_type axis)
    {
      types::ndarray<T, 1> out(
          types::make_tuple(long(in.flat_size() + std::min(indices.flat_size(),
                                                           data.flat_size()))),
          __builtin__::None);
      auto out_iter = out.fbegin();
      auto in_iter = in.fbegin();
      auto data_iter = data.begin();
      for (long index : indices) {
        out_iter = std::copy(in_iter, in.fbegin() + index, out_iter);
        *out_iter++ = *data_iter++;
        in_iter = in.fbegin() + index;
      }
      std::copy(in_iter, in.fend(), out_iter);
      return out;
    }

    template <class T, size_t N, class I, class F>
    typename std::enable_if<types::is_iterable<I>::value and
                                not types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis)
    {
      return insert(in, indices, types::list<F>({data}), axis);
    }

    template <class T, size_t N, class I, class F>
    typename std::enable_if<not types::is_iterable<I>::value and
                                types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis)
    {
      return insert(in, types::list<I>({indices}), {data}, axis);
    }

    template <class T, size_t N, class I, class F>
    typename std::enable_if<not types::is_iterable<I>::value and
                                not types::is_iterable<F>::value,
                            types::ndarray<T, 1>>::type
    insert(types::ndarray<T, N> in, I const &indices, F const &data,
           types::none_type axis)
    {
      return insert(in, types::list<I>({indices}), types::list<F>({data}),
                    axis);
    }

    template <class E, class... Args>
    E insert(E, Args const &...)
    {
      throw std::runtime_error("insert only partially supported");
    }

    DEFINE_FUNCTOR(pythonic::numpy, insert);
  }
}

#endif
