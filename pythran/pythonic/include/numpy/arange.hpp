#ifndef PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARANGE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/operator_/pos.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace details
  {
    template <class T>
    struct arange_index {
      T start, step;
      long size;
      using iterator = types::nditerator<arange_index>;
      using const_iterator = types::const_nditerator<arange_index>;
      using dtype = T;
      using value_type = dtype;
      using shape_t = types::pshape<long>;
#ifdef USE_XSIMD
      using simd_iterator = types::const_simd_nditerator<arange_index>;
      using simd_iterator_nobroadcast = simd_iterator;
      template <class vectorizer>
      simd_iterator vbegin(vectorizer) const;
      template <class vectorizer>
      simd_iterator vend(vectorizer) const;
#endif
      static constexpr size_t value = 1;
      static constexpr bool is_strided = false;
      static constexpr bool is_vectorizable =
          false; // FIXME: this is feasible, but I'm lazy

      T fast(long i) const
      {
        return start + i * step;
      }

      shape_t shape() const
      {
        return {size};
      }
      types::ndarray<dtype, shape_t> operator[](types::slice s) const
      {
        auto ns = s.normalize(size);
        arange_index r{start + s.lower * step, step * ns.step, ns.size()};
        return {
            types::numpy_expr<pythonic::operator_::functor::pos, arange_index>{
                r}};
      }
      types::ndarray<dtype, shape_t> operator()(types::slice s) const
      {
        return operator[](s);
      }

      template <class L, class U>
      types::ndarray<dtype, shape_t>
      operator[](types::contiguous_slice<L, U> s) const
      {
        auto ns = s.normalize(size);
        arange_index r{start + s.lower * step, step, ns.size()};
        return {
            types::numpy_expr<pythonic::operator_::functor::pos, arange_index>{
                r}};
      }

      template <class L, class U>
      types::ndarray<dtype, shape_t>
      operator()(types::contiguous_slice<L, U> s) const
      {
        return operator[](s);
      }
      const_iterator begin() const
      {
        return {*this, 0};
      }
      const_iterator end() const
      {
        return {*this, size};
      }

      iterator begin()
      {
        return {*this, 0};
      }
      iterator end()
      {
        return {*this, size};
      }
    };
  }

  template <class T, class U, class S = long,
            class dtype = types::dtype_t<typename __combined<T, U, S>::type>>
  types::numpy_expr<pythonic::operator_::functor::pos,
                    details::arange_index<typename dtype::type>>
  arange(T begin, U end, S step = S(1), dtype d = dtype());

  template <class T>
  types::numpy_expr<pythonic::operator_::functor::pos,
                    details::arange_index<typename types::dtype_t<T>::type>>
  arange(T end);

  DEFINE_FUNCTOR(pythonic::numpy, arange);
}
PYTHONIC_NS_END

#endif
