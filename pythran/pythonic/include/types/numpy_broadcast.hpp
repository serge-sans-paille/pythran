#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_BROADCAST_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_BROADCAST_HPP

#ifdef USE_BOOST_SIMD
#include <boost/simd/pack.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#endif

#include "pythonic/include/types/vectorizable_type.hpp"
#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  struct broadcasted_iterator
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<T>::type> {
    T value_;

    broadcasted_iterator(T const &value) : value_(value)
    {
    }

    T const &operator*() const
    {
      return value_;
    }

    broadcasted_iterator &operator++()
    {
      return *this;
    }

    broadcasted_iterator &operator+=(long i)
    {
      return *this;
    }

    long operator-(broadcasted_iterator const &other) const
    {
      return 0;
    }

    bool operator!=(broadcasted_iterator const &other) const
    {
      return false;
    }
    bool operator==(broadcasted_iterator const &other) const
    {
      return true;
    }
    bool operator<(broadcasted_iterator const &other) const
    {
      return false;
    }
  };

  /* Type adaptor for broadcasted array values
   *
   * Used when the args of a binary operator do ! have the same dimensions:
   * in that case their first dimension always yields a copy
   */
  template <class T>
  struct broadcasted {
    static const bool is_vectorizable = true;
    static const bool is_strided = false;
    using dtype = typename std::remove_reference<T>::type::dtype;
    using value_type = typename std::remove_reference<T>::type::value_type;
    static constexpr size_t value = std::remove_reference<T>::type::value + 1;
    using const_iterator = broadcasted_iterator<T>;
    using iterator = const_iterator;

    T const ref;
    types::array<long, value> _shape;
    types::array<long, value> const &shape() const
    {
      return _shape;
    }

    broadcasted() = default;

    broadcasted(T const &ref);
    const_iterator begin() const
    {
      return {ref};
    }
    const_iterator end() const
    {
      return {ref};
    }

    T const &operator[](long i) const;
    T const &fast(long i) const;
#ifdef USE_BOOST_SIMD
    using simd_iterator = const_simd_nditerator_nostep<broadcasted>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    template <class Arg0, class... Args>
    auto operator()(Arg0 &&arg0, Args &&... args) const
        -> decltype(ref(std::forward<Args>(args)...));

    long flat_size() const;
  };

  /* Type adaptor for scalar values
   *
   * Have them behave like infinite arrays of that value
   *
   * B is the original type of the broadcast value, && T is the type of the
   *expression it is combined with
   * if both B && T are integer types, we choose T instead of B to prevent
   *automatic conversion into larger types
   *
   * That way, np.ones(10, dtype=np.uint8) + 1 yields an array of np.uint8,
   *although 1 is of type long
   */
  template <class dtype, bool is_vectorizable>
  struct broadcast_base {
    dtype _value;
    struct ignored {
    } _splated;
    broadcast_base() = default;
    template <class V>
    broadcast_base(V v);
    template <class I>
    void load(I) const;
  };

#ifdef USE_BOOST_SIMD
  template <class dtype>
  struct broadcast_base<dtype, true> {
    dtype _value;
    boost::simd::pack<dtype> _splated;
    broadcast_base() = default;

    template <class V>
    broadcast_base(V v);
    template <class I>
    auto load(I) const -> decltype(this->_splated);
  };
#endif

  template <class T>
  struct const_broadcast_iterator
      : public std::iterator<std::random_access_iterator_tag, T> {
    T value;
    const_broadcast_iterator(T data) : value{data}
    {
    }

    T operator*() const
    {
      return value;
    }
    const_broadcast_iterator &operator++()
    {
      return *this;
    }
    const_broadcast_iterator &operator--()
    {
      return *this;
    }
    const_broadcast_iterator &operator+=(long i)
    {
      return *this;
    }
    const_broadcast_iterator &operator-=(long i)
    {
      return *this;
    }
    const_broadcast_iterator operator+(long i) const
    {
      return *this;
    }
    const_broadcast_iterator operator-(long i) const
    {
      return *this;
    }
    long operator-(const_broadcast_iterator const &other) const
    {
      return 0;
    }
    bool operator!=(const_broadcast_iterator const &other) const
    {
      return false;
    }
    bool operator==(const_broadcast_iterator const &other) const
    {
      return true;
    }
    bool operator<(const_broadcast_iterator const &other) const
    {
      return false;
    }
    const_broadcast_iterator &operator=(const_broadcast_iterator const &other)
    {
      return *this;
    }
  };

  template <class T, class B>
  struct broadcast {
    // Perform the type conversion here if it seems valid (although it is !
    // always)
    using dtype =
        typename std::conditional<std::is_integral<T>::value &&
                                      std::is_integral<B>::value,
                                  T, typename __combined<T, B>::type>::type;
    static const bool is_vectorizable = types::is_vectorizable<dtype>::value;
    static const bool is_strided = false;
    using value_type = dtype;
    using const_iterator = const_broadcast_iterator<dtype>;
    using iterator = const_iterator;
    static constexpr size_t value = 0;

    broadcast_base<dtype, is_vectorizable> _base;
    operator dtype() const
    {
      return _base._value;
    }

    broadcast() = default;
    template <class V>
    broadcast(V v);

    dtype operator[](long) const;
    dtype fast(long) const;
    template <class I>
    auto load(I i) const -> decltype(this->_base.load(i));
    template <class... Args>
    dtype operator()(Args &&...) const;
    array<long, 1> shape() const;
    long flat_size() const;
    const_iterator begin() const
    {
      return {_base._value};
    }
    const_iterator end() const
    {
      return {_base._value};
    }
#ifdef USE_BOOST_SIMD
    using simd_iterator = const_broadcast_iterator<decltype(_base._splated)>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const
    {
      return {_base._splated};
    }
    template <class vectorizer>
    simd_iterator vend(vectorizer) const
    {
      return {_base._splated};
    }
#endif
  };
}
PYTHONIC_NS_END

#endif
