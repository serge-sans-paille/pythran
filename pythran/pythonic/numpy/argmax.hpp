#ifndef PYTHONIC_NUMPY_ARGMAX_HPP
#define PYTHONIC_NUMPY_ARGMAX_HPP

#include "pythonic/include/numpy/argmax.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class I0, class T>
    long _argmax(I0 begin, I0 end, T &max_elts, utils::int_<1>)
    {
      auto local_max_elts = std::max_element(begin, end);
      if (*local_max_elts > max_elts) {
        max_elts = *local_max_elts;
        return local_max_elts - begin;
      }

      return -1;
    }

    template <class I0, size_t N, class T>
    long _argmax(I0 begin, I0 end, T &max_elts, utils::int_<N>)
    {
      long current_pos = 0;
      long current_maxarg = 0;
      for (; begin != end; ++begin) {
        long v = _argmax((*begin).begin(), (*begin).end(), max_elts,
                         utils::int_<N - 1>());
        if (v >= 0)
          current_maxarg = current_pos + v;
        current_pos += (*begin).flat_size();
      }
      return current_maxarg;
    }

    template <class E>
    long argmax(E const &expr)
    {
      if (not expr.flat_size())
        throw types::ValueError("empty sequence");
      using elt_type = typename E::dtype;
      elt_type argmax_value = std::numeric_limits<elt_type>::lowest();
      ;
      return _argmax(expr.begin(), expr.end(), argmax_value,
                     utils::int_<E::value>());
    }

    DEFINE_FUNCTOR(pythonic::numpy, argmax);
  }
}

#endif
