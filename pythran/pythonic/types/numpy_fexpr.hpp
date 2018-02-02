#ifndef PYTHONIC_TYPES_NUMPY_FEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_FEXPR_HPP

#include "pythonic/include/types/numpy_fexpr.hpp"

#include "pythonic/types/nditerator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Arg, class F>
  numpy_fexpr<Arg, F>::numpy_fexpr(Arg const &arg, F const &filter)
      : arg(arg), indices(arg.flat_size()), buffer(indices->data)
  {
    auto iter = buffer;
    long index = 0;
    _copy_mask(filter.begin(), filter.end(), iter, index,
               utils::int_<std::remove_reference<
                   typename std::remove_cv<Arg>::type>::type::value>());
    // FIXME {iter - buffer} is a long long int? (Windows say that...
    // && warn us)
    _shape[0] = {iter - buffer};
  }

  template <class Arg, class F>
  template <class FIter, class O>
  void numpy_fexpr<Arg, F>::_copy_mask(FIter fiter, FIter fend, O &out,
                                       long &index, utils::int_<1>)
  {
    for (; fiter != fend; ++fiter, ++index)
      if (*fiter)
        *out++ = index;
  }

  template <class Arg, class F>
  template <class FIter, class O, size_t N>
  void numpy_fexpr<Arg, F>::_copy_mask(FIter fiter, FIter fend, O &out,
                                       long &index, utils::int_<N>)
  {
    for (; fiter != fend; ++fiter)
      _copy_mask((*fiter).begin(), (*fiter).end(), out, index,
                 utils::int_<N - 1>());
  }

  template <class Arg, class F>
  template <class E>
  typename std::enable_if<is_iterable<E>::value, numpy_fexpr<Arg, F> &>::type
      numpy_fexpr<Arg, F>::
      operator=(E const &expr)
  {
    std::copy(expr.begin(), expr.end(), begin());
    return *this;
  }

  template <class Arg, class F>
  template <class E>
  typename std::enable_if<!is_iterable<E>::value, numpy_fexpr<Arg, F> &>::type
      numpy_fexpr<Arg, F>::
      operator=(E const &expr)
  {
    std::fill(begin(), end(), expr);
    return *this;
  }

  template <class Arg, class F>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator=(numpy_fexpr const &expr)
  {
    std::copy(expr.begin(), expr.end(), begin());
    return *this;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator+=(E const &expr)
  {
    return *(this) = *this + expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator-=(E const &expr)
  {
    return *(this) = *this - expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator*=(E const &expr)
  {
    return *(this) = *this * expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator/=(E const &expr)
  {
    return *(this) = *this / expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator&=(E const &expr)
  {
    return *(this) = *this & expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator|=(E const &expr)
  {
    return *(this) = *this | expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator>>=(E const &expr)
  {
    return *(this) = *this >> expr;
  }

  template <class Arg, class F>
  template <class E>
  numpy_fexpr<Arg, F> &numpy_fexpr<Arg, F>::operator<<=(E const &expr)
  {
    return *(this) = *this << expr;
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::const_iterator
  numpy_fexpr<Arg, F>::begin() const
  {
    return {*this, 0};
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::const_iterator numpy_fexpr<Arg, F>::end() const
  {
    return {*this, _shape[0]};
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::iterator numpy_fexpr<Arg, F>::begin()
  {
    return {*this, 0};
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::iterator numpy_fexpr<Arg, F>::end()
  {
    return {*this, _shape[0]};
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::dtype numpy_fexpr<Arg, F>::fast(long i) const
  {
    return *(arg.fbegin() + buffer[i]);
  }

  template <class Arg, class F>
  typename numpy_fexpr<Arg, F>::dtype &numpy_fexpr<Arg, F>::fast(long i)
  {
    return *(arg.fbegin() + buffer[i]);
  }

#ifdef USE_BOOST_SIMD
  template <class Arg, class F>
  template <class vectorizer>
  typename numpy_fexpr<Arg, F>::simd_iterator
      numpy_fexpr<Arg, F>::vbegin(vectorizer) const
  {
    return {*this, 0};
  }

  template <class Arg, class F>
  template <class vectorizer>
  typename numpy_fexpr<Arg, F>::simd_iterator
      numpy_fexpr<Arg, F>::vend(vectorizer) const
  {
    using vector_type = typename boost::simd::pack<dtype>;
    static const std::size_t vector_size = vector_type::static_size;
    return {*this, long(_shape[0] / vector_size * vector_size)};
  }
#endif
  template <class Arg, class F>
  auto numpy_fexpr<Arg, F>::operator[](long i) const -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class Arg, class F>
  auto numpy_fexpr<Arg, F>::operator[](long i) -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class Arg, class F>
  template <class E>
  typename std::enable_if<is_numexpr_arg<E>::value,
                          numpy_fexpr<numpy_fexpr<Arg, F>, E>>::type
  numpy_fexpr<Arg, F>::fast(E const &expr) const
  {
    return numpy_fexpr<numpy_fexpr, E>(*this, expr);
  }

  template <class Arg, class F>
  template <class E>
  typename std::enable_if<is_numexpr_arg<E>::value,
                          numpy_fexpr<numpy_fexpr<Arg, F>, E>>::type
      numpy_fexpr<Arg, F>::
      operator[](E const &expr) const
  {
    return fast(expr);
  }

  template <class Arg, class F>
  long numpy_fexpr<Arg, F>::flat_size() const
  {
    return _shape[0];
  }
}
PYTHONIC_NS_END

#endif
