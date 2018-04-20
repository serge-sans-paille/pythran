#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_VEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_VEXPR_HPP

#include "pythonic/include/types/nditerator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T, class F>
  struct numpy_vexpr {

    static constexpr size_t value = T::value;
    static const bool is_vectorizable = false;
    using dtype = typename dtype_of<T>::type;
    using value_type = T;
    static constexpr bool is_strided = T::is_strided;

    using iterator = nditerator<numpy_vexpr>;
    using const_iterator = const_nditerator<numpy_vexpr>;

    T data_;
    F view_;

    numpy_vexpr(T const &data, F const &view) : data_{data}, view_{view}
    {
    }

    long flat_size() const
    {
      auto data_shape = data_.shape();
      return std::accumulate(data_shape.begin() + 1, data_shape.end(),
                             view_.shape()[0], std::multiplies<long>());
    }

    long size() const
    {
      return view_.size();
    }

    template <class E>
    numpy_vexpr &operator=(E const &);
    numpy_vexpr &operator=(numpy_vexpr const &);

    array<long, value> shape() const
    {
      array<long, value> res = data_.shape();
      res.fast(0) = view_.shape()[0];
      return res;
    }

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
#ifdef USE_BOOST_SIMD
    using simd_iterator = const_simd_nditerator<numpy_vexpr>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    auto fast(long i) -> decltype(data_.fast(i))
    {
      return data_.fast(view_.fast(i));
    }
    auto fast(long i) const -> decltype(data_.fast(i))
    {
      return data_.fast(view_.fast(i));
    }
    template <class... S>
    auto operator()(S const &... slices) const
        -> decltype(ndarray<dtype, value>{*this}(slices...));

    auto operator[](long i) const -> decltype(data_[i])
    {
      return data_.fast(view_[i]);
    }
    numpy_gexpr<numpy_vexpr, slice> operator[](slice s) const
    {
      return {*this, s};
    }
    numpy_gexpr<numpy_vexpr, contiguous_slice>
    operator[](contiguous_slice s) const
    {
      return {*this, s};
    }
  };
}

template <class T, class F>
struct assignable<types::numpy_vexpr<T, F>> {
  using type = types::ndarray<typename types::dtype_of<T>::type, T::value>;
};
PYTHONIC_NS_END

#endif
