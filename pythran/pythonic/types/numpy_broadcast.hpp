#ifndef PYTHONIC_TYPES_NUMPY_BROADCAST_HPP
#define PYTHONIC_TYPES_NUMPY_BROADCAST_HPP

#include "pythonic/include/types/numpy_broadcast.hpp"

#include "pythonic/types/vectorizable_type.hpp"
#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class T>
  broadcasted<T>::broadcasted(T const &ref)
      : ref(ref), _shape()
  {
    sutils::copy_shape<1, -1>(_shape, ref.shape(),
                              utils::make_index_sequence<T::value>());
  }

  template <class T>
  T const &broadcasted<T>::operator[](long i) const
  {
    return ref;
  }

  template <class T>
  T const &broadcasted<T>::fast(long i) const
  {
    return ref;
  }

#ifdef USE_XSIMD
  template <class T>
  template <class vectorizer>
  typename broadcasted<T>::simd_iterator
      broadcasted<T>::vbegin(vectorizer) const
  {
    return {*this};
  }

  template <class T>
  template <class vectorizer>
  typename broadcasted<T>::simd_iterator broadcasted<T>::vend(vectorizer) const
  {
    return {*this}; // should ! happen anyway
  }

#endif

  template <class T>
  template <class Arg1, class... Args>
  auto broadcasted<T>::operator()(long arg0, Arg1 &&arg1, Args &&... args) const
      -> decltype(ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...))
  {
    return ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...);
  }

  template <class T>
  template <class Arg1, class... Args>
  auto broadcasted<T>::operator()(slice arg0, Arg1 &&arg1,
                                  Args &&... args) const
      -> decltype(ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...))
  {
    return {ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...)};
  }

  template <class T>
  template <class L, class U, class Arg1, class... Args>
  auto broadcasted<T>::operator()(contiguous_slice<L, U> arg0, Arg1 &&arg1,
                                  Args &&... args) const
      -> decltype(ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...))
  {
    return {ref(std::forward<Arg1>(arg1), std::forward<Args>(args)...)};
  }

  template <class T>
  long broadcasted<T>::flat_size() const
  {
    return 0;
  }

  template <class dtype, bool is_vectorizable>
  template <class V>
  broadcast_base<dtype, is_vectorizable>::broadcast_base(V v)
      : _value(v)
  {
  }

#ifdef USE_XSIMD
  template <class dtype>
  template <class V>
  broadcast_base<dtype, true>::broadcast_base(V v)
      : _value(v), _splated(xsimd::simd_type<dtype>(_value))
  {
  }

#endif

  template <class T, class B>
  template <class V>
  broadcast<T, B>::broadcast(V v)
      : _base(v)
  {
  }

  template <class T, class B>
  typename broadcast<T, B>::dtype broadcast<T, B>::operator[](long) const
  {
    return _base._value;
  }

  template <class T, class B>
  template <size_t N>
  typename broadcast<T, B>::dtype broadcast<T, B>::
  operator[](array<long, N>) const
  {
    return _base._value;
  }

  template <class T, class B>
  typename broadcast<T, B>::dtype broadcast<T, B>::fast(long) const
  {
    return _base._value;
  }

  template <class T, class B>
  template <class... Args>
  typename broadcast<T, B>::dtype broadcast<T, B>::
  operator()(Args &&... args) const
  {
    return _base._value;
  }

  template <class T, class B>
  typename broadcast<T, B>::shape_t broadcast<T, B>::shape() const
  {
    return {};
  }

  template <class T, class B>
  long broadcast<T, B>::flat_size() const
  {
    return 0;
  }
}
PYTHONIC_NS_END

#endif
