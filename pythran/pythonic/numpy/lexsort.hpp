#ifndef PYTHONIC_NUMPY_LEXSORT_HPP
#define PYTHONIC_NUMPY_LEXSORT_HPP

#include "pythonic/include/numpy/lexsort.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace details
    {

      template <size_t I>
      struct lexcmp_nth {
        template <class K>
        bool operator()(K const &keys, long i0, long i1) const
        {
          if (std::get<I - 1>(keys)[i0] < std::get<I - 1>(keys)[i1])
            return true;
          else if (std::get<I - 1>(keys)[i0] > std::get<I - 1>(keys)[i1])
            return false;
          else
            return lexcmp_nth<I - 1>{}(keys, i0, i1);
        }
      };
      template <>
      struct lexcmp_nth<0> {
        template <class K>
        bool operator()(K const &keys, long i0, long i1) const
        {
          return false;
        }
      };

      template <class K>
      struct lexcmp {
        K const &keys;
        lexcmp(K const &keys) : keys(keys)
        {
        }
        bool operator()(long i0, long i1)
        {
          return lexcmp_nth<std::tuple_size<K>::value>{}(keys, i0, i1);
        }
      };

      template <class K>
      types::ndarray<long, 1> lexsort(K const &keys)
      {
        long n = std::get<0>(keys).size();
        types::ndarray<long, 1> out(types::make_tuple(n), __builtin__::None);
        // fill with the original indices
        std::iota(out.buffer, out.buffer + n, 0L);
        // then sort using keys as the comparator
        std::sort(out.buffer, out.buffer + n, details::lexcmp<K>(keys));
        return out;
      }
    }

    template <class T, size_t N>
    types::ndarray<long, 1> lexsort(types::array<T, N> const &keys)
    {
      return details::lexsort(keys);
    }
    template <class... Types>
    types::ndarray<long, 1> lexsort(std::tuple<Types...> const &keys)
    {
      return details::lexsort(keys);
    }

    DEFINE_FUNCTOR(pythonic::numpy, lexsort)
  }
}

#endif
