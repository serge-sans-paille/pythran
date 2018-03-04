#ifndef PYTHONIC_NUMPY_ARGMINMAX_HPP
#define PYTHONIC_NUMPY_ARGMINMAX_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class Op, class I0, class T>
  long _argminmax(I0 begin, I0 end, T &minmax_elts, utils::int_<1>)
  {
    auto local_minmax_elts = Op::elements(begin, end);
    if (Op::value(*local_minmax_elts, minmax_elts)) {
      minmax_elts = *local_minmax_elts;
      return local_minmax_elts - begin;
    }

    return -1;
  }

  template <class Op, class I0, size_t N, class T>
  long _argminmax(I0 begin, I0 end, T &minmax_elts, utils::int_<N>)
  {
    long current_pos = 0;
    long current_minmaxarg = 0;
    for (; begin != end; ++begin) {
      long v = _argminmax<Op>((*begin).begin(), (*begin).end(), minmax_elts,
                              utils::int_<N - 1>());
      if (v >= 0)
        current_minmaxarg = current_pos + v;
      current_pos += (*begin).flat_size();
    }
    return current_minmaxarg;
  }

  template <class Op, class E>
  long argminmax(E const &expr)
  {
    if (!expr.flat_size())
      throw types::ValueError("empty sequence");
    using elt_type = typename E::dtype;
    elt_type argminmax_value = Op::limit();
    ;
    return _argminmax<Op>(expr.begin(), expr.end(), argminmax_value,
                          utils::int_<E::value>());
  }
}
PYTHONIC_NS_END

#endif
