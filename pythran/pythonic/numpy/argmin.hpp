#ifndef PYTHONIC_NUMPY_ARGMIN_HPP
#define PYTHONIC_NUMPY_ARGMIN_HPP

#include "pythonic/include/numpy/argmin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I0, class T>
    long _argmin(I0 begin, I0 end, T &min_elts, utils::int_<1>)
    {
      auto local_min_elts = std::min_element(begin, end);
      if (*local_min_elts < min_elts) {
        min_elts = *local_min_elts;
        return local_min_elts - begin;
      }

      return -1;
    }

    template <class I0, size_t N, class T>
    long _argmin(I0 begin, I0 end, T &min_elts, utils::int_<N>)
    {
      long current_pos = 0;
      long current_minarg = 0;
      for (; begin != end; ++begin) {
        long v = _argmin((*begin).begin(), (*begin).end(), min_elts,
                         utils::int_<N - 1>());
        if (v >= 0)
          current_minarg = current_pos + v;
        current_pos += (*begin).flat_size();
      }
      return current_minarg;
    }

    template <class E>
    long argmin(E const &expr)
    {
      if (not expr.flat_size())
        throw types::ValueError("empty sequence");
      using elt_type = typename E::dtype;
      elt_type argmin_value = std::numeric_limits<elt_type>::max();
      ;
      return _argmin(expr.begin(), expr.end(), argmin_value,
                     utils::int_<E::value>());
    }

    DEFINE_FUNCTOR(pythonic::numpy, argmin);
  }
}

#endif
