#ifndef PYTHONIC_TYPES_NUMPY_BROADCAST_HPP
#define PYTHONIC_TYPES_NUMPY_BROADCAST_HPP

#include "pythonic/include/types/numpy_broadcast.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include "pythonic/types/vectorizable_type.hpp"
#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/tuple.hpp"

namespace pythonic
{

  namespace types
  {

    template <class T>
    types::array<long, broadcasted<T>::value> const &
    broadcasted<T>::shape() const
    {
      return _shape;
    }

    template <class T>
    broadcasted<T>::broadcasted(T const &ref)
        : ref(ref), _shape()
    {
      _shape[0] = 1;
      auto &&ref_shape = ref.shape();
      std::copy(ref_shape.begin(), ref_shape.end(), _shape.begin() + 1);
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

#ifdef USE_BOOST_SIMD
    template <class T>
    typename broadcasted<T>::simd_iterator broadcasted<T>::vbegin() const
    {
      return {*this, 0};
    }

    template <class T>
    typename broadcasted<T>::simd_iterator broadcasted<T>::vend() const
    {
      return {*this, 0}; // should not happen anyway
    }

    template <class T>
    template <class I> // template to prevent automatic instantiation, but the
    // declaration is still needed
    void broadcasted<T>::load(I) const
    {
      static_assert(I::this_should_never_happen, "this is *not* vectorizable");
    }
#endif

    template <class T>
    template <class Arg0, class... Args>
    auto broadcasted<T>::operator()(Arg0 &&arg0, Args &&... args) const
        -> decltype(ref(std::forward<Args>(args)...))
    {
      return ref(std::forward<Args>(args)...);
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

    template <class dtype, bool is_vectorizable>
    template <class I>
    void broadcast_base<dtype, is_vectorizable>::load(I) const
    {
      static_assert(sizeof(I) != sizeof(I),
                    "this method should never be instantiated");
    }

#ifdef USE_BOOST_SIMD
    template <class dtype>
    template <class V>
    broadcast_base<dtype, true>::broadcast_base(V v)
        : _value(v),
          _splated(boost::simd::splat<
              boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(_value))
    {
    }

    template <class dtype>
    template <class I>
    auto broadcast_base<dtype, true>::load(I) const -> decltype(this->_splated)
    {
      return _splated;
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
    typename broadcast<T, B>::dtype broadcast<T, B>::fast(long) const
    {
      return _base._value;
    }

    template <class T, class B>
    template <class I>
    auto broadcast<T, B>::load(I i) const -> decltype(this->_base.load(i))
    {
      return _base.load(i);
    }
    template <class T, class B>
    template <class... Args>
    typename broadcast<T, B>::dtype broadcast<T, B>::
    operator()(Args &&... args) const
    {
      return _base._value;
    }

    template <class T, class B>
    array<long, 1> broadcast<T, B>::shape() const
    {
      return {0};
    }

    template <class T, class B>
    long broadcast<T, B>::flat_size() const
    {
      return 0;
    }
  }
}

#endif
