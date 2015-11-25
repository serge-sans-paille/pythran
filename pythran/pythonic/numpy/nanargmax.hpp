#ifndef PYTHONIC_NUMPY_NANARGMAX_HPP
#define PYTHONIC_NUMPY_NANARGMAX_HPP

#include "pythonic/include/numpy/nanargmax.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/isnan.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    void _nanargmax(E begin, E end, F &max, long &index, long &where,
                    utils::int_<1>)
    {
      for (; begin != end; ++begin, ++index) {
        auto curr = *begin;
        if (not functor::isnan()(curr) and curr > max) {
          max = curr;
          where = index;
        }
      }
    }

    template <class E, class F, size_t N>
    void _nanargmax(E begin, E end, F &max, long &index, long &where,
                    utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _nanargmax((*begin).begin(), (*begin).end(), max, index, where,
                   utils::int_<N - 1>());
    }

    template <class E>
    typename E::dtype nanargmax(E const &expr)
    {
      typename E::dtype max =
          -std::numeric_limits<typename E::dtype>::infinity();
      long where = -1;
      long index = 0;
      _nanargmax(expr.begin(), expr.end(), max, index, where,
                 utils::int_<E::value>());
      if (where >= 0)
        return where;
      else
        throw types::ValueError("empty sequence");
    }

    DEFINE_FUNCTOR(pythonic::numpy, nanargmax);
  }
}

#endif
