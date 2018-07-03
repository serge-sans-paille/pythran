#ifndef PYTHONIC_NUMPY_UNRAVEL_INDEX_HPP
#define PYTHONIC_NUMPY_UNRAVEL_INDEX_HPP

#include "pythonic/include/numpy/unravel_index.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace
  {
    template <class E, class ShapeIt, class RetIt>
    void _unravel_index(E expr, ShapeIt shape_it, ShapeIt end_it, RetIt ret_it)
    {
      while (shape_it != end_it) {
        auto &v = *shape_it;
        *ret_it = expr % v;
        expr /= v;
        ++shape_it;
        ++ret_it;
      }
    }
  }

  template <class E, class IntTy, size_t N>
  typename std::enable_if<std::is_scalar<E>::value,
                          types::array<IntTy, N>>::type
  unravel_index(E const &expr, types::array<IntTy, N> const &shape,
                types::str const &order)
  {
    types::array<IntTy, N> ret;
    if (order[0] == 'C') {
      _unravel_index(expr, shape.rbegin(), shape.rend(), ret.rbegin());
    } else if (order[0] == 'F') {
      _unravel_index(expr, shape.begin(), shape.end(), ret.begin());
    } else {
      throw types::ValueError("Invalid order");
    }
    return ret;
  }
}
PYTHONIC_NS_END

#endif
