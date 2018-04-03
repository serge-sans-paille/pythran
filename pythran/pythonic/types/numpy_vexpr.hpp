#ifndef PYTHONIC_TYPES_NUMPY_VEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_VEXPR_HPP

PYTHONIC_NS_BEGIN

namespace types
{

  template <class T, class F>
  template <class E>
  numpy_vexpr<T, F> &numpy_vexpr<T, F>::operator=(E const &expr)
  {
    // TODO: avoid the tmp copy when no aliasing
    typename assignable<E>::type tmp{expr};
    for (long i = 0, n = tmp.shape()[0]; i < n; ++i)
      (*this).fast(i) = tmp.fast(i);
    return *this;
  }
  template <class T, class F>
  numpy_vexpr<T, F> &numpy_vexpr<T, F>::operator=(numpy_vexpr<T, F> const &expr)
  {
    // TODO: avoid the tmp copy when no aliasing
    typename assignable<numpy_vexpr<T, F>>::type tmp{expr};
    for (long i = 0, n = tmp.shape()[0]; i < n; ++i)
      (*this).fast(i) = tmp.fast(i);
    return *this;
  }

  template <class T, class F>
  typename numpy_vexpr<T, F>::iterator numpy_vexpr<T, F>::begin()
  {
    return {*this, 0};
  }
  template <class T, class F>
  typename numpy_vexpr<T, F>::iterator numpy_vexpr<T, F>::end()
  {
    return {*this, shape()[0]};
  }
  template <class T, class F>
  typename numpy_vexpr<T, F>::const_iterator numpy_vexpr<T, F>::begin() const
  {
    return {*this, 0};
  }
  template <class T, class F>
  typename numpy_vexpr<T, F>::const_iterator numpy_vexpr<T, F>::end() const
  {
    return {*this, shape()[0]};
  }
  template <class T, class F>
  template <class... S>
  auto numpy_vexpr<T, F>::operator()(S const &... slices) const
      -> decltype(ndarray<dtype, value>{*this}(slices...))
  {
    return ndarray<dtype, value>{*this}(slices...);
  }
#ifdef USE_BOOST_SIMD
  template <class Arg, class F>
  template <class vectorizer>
  typename numpy_vexpr<Arg, F>::simd_iterator
      numpy_vexpr<Arg, F>::vbegin(vectorizer) const
  {
    return {*this, 0};
  }

  template <class Arg, class F>
  template <class vectorizer>
  typename numpy_vexpr<Arg, F>::simd_iterator
      numpy_vexpr<Arg, F>::vend(vectorizer) const
  {
    using vector_type = typename boost::simd::pack<dtype>;
    static const std::size_t vector_size = vector_type::static_size;
    return {*this, 0};
  }
#endif
}
PYTHONIC_NS_END

#endif
