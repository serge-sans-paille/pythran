#ifndef PYTHONIC_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/include/types/numpy_iexpr.hpp"

#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/tuple.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <numeric>

namespace pythonic
{

  namespace types
  {

    template <class Arg>
    numpy_iexpr<Arg>::numpy_iexpr()
    {
    }

    template <class Arg>
    template <class Argp> // not using the default one, to make it possible to
    // accept reference and non reference version of Argp
    numpy_iexpr<Arg>::numpy_iexpr(numpy_iexpr<Argp> const &other)
        : arg(other.arg), buffer(other.buffer), _shape(other.shape())
    {
    }

    template <class Arg>
    numpy_iexpr<Arg>::numpy_iexpr(Arg const &arg, long index)
        : arg(arg), buffer(arg.buffer)
    {
      buffer += buffer_offset(index, utils::int_<value>());
    }

    // force the move. Using universal reference here does not work (because of
    // reference collapsing ?)
    template <class Arg>
    numpy_iexpr<Arg>::numpy_iexpr(
        typename std::remove_reference<Arg>::type &&arg, long index)
        : arg(std::move(arg)), buffer(arg.buffer)
    {
      buffer += buffer_offset(index, utils::int_<value>());
    }

    template <class Arg>
    long numpy_iexpr<Arg>::size() const
    {
      return _shape[0];
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator=(E const &expr)
    {
      return utils::broadcast_copy<numpy_iexpr &, E, value,
                                   value - utils::dim_of<E>::value,
                                   false /*NIY*/>(*this, expr);
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator=(numpy_iexpr<Arg> const &expr)
    {
      return utils::broadcast_copy<numpy_iexpr &, numpy_iexpr const &, value,
                                   value - utils::dim_of<numpy_iexpr>::value,
                                   false /*NIY*/>(*this, expr);
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator+=(E const &expr)
    {
      return (*this) = (*this) + expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator+=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) + expr;
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator-=(E const &expr)
    {
      return (*this) = (*this) - expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator-=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) - expr;
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator*=(E const &expr)
    {
      return (*this) = (*this) * expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator*=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) * expr;
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator/=(E const &expr)
    {
      return (*this) = (*this) / expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator/=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) / expr;
    }

    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator&=(E const &expr)
    {
      return (*this) = (*this) & expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator&=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) & expr;
    }
    template <class Arg>
    template <class E>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator|=(E const &expr)
    {
      return (*this) = (*this) | expr;
    }

    template <class Arg>
    numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator|=(numpy_iexpr<Arg> const &expr)
    {
      return (*this) = (*this) | expr;
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::begin() const
    {
      return make_const_nditerator < is_strided or value != 1 > ()(*this, 0);
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::end() const
    {
      return make_const_nditerator < is_strided or
             value != 1 > ()(*this, _shape[0]);
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::begin()
    {
      return make_nditerator < is_strided or value != 1 > ()(*this, 0);
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::end()
    {
      return make_nditerator < is_strided or value != 1 > ()(*this, _shape[0]);
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fbegin() const
    {
      return buffer;
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fend() const
    {
      return buffer + flat_size();
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype *numpy_iexpr<Arg>::fbegin()
    {
      return buffer;
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fend()
    {
      return buffer + flat_size();
    }

    template <class Arg>
    auto numpy_iexpr<Arg>::fast(long i) const
        & -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(*this,
                                                                       i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::fast(long i) &
        -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(*this, i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::fast(long i) &&
        -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(
            std::move(*this), i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i);
    }

#ifdef USE_BOOST_SIMD
    template <class Arg>
    typename numpy_iexpr<Arg>::simd_iterator numpy_iexpr<Arg>::vbegin() const
    {
      return {*this, 0};
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::simd_iterator numpy_iexpr<Arg>::vend() const
    {
      using vector_type =
          typename boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>;
      static const std::size_t vector_size =
          boost::simd::meta::cardinal_of<vector_type>::value;
      return {*this, long(_shape[0] / vector_size * vector_size)};
    }

    template <class Arg>
    template <class I>
    auto numpy_iexpr<Arg>::load(I i) const -> decltype(boost::simd::load<
        boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(this->buffer,
                                                                  i))
    {
      using T = dtype;
      using vT = typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
      return boost::simd::load<vT>(buffer, i);
    }

    template <class Arg>
    template <class V>
    void numpy_iexpr<Arg>::store(V &&v, long i)
    {
      boost::simd::store(v, buffer, i);
    }
#endif
    template <class Arg>
    auto numpy_iexpr<Arg>::operator[](long i) const & -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::operator[](long i) & -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::operator[](long i) &&
        -> decltype(std::move(*this).fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return std::move(*this).fast(i);
    }

    template <class Arg>
    auto numpy_iexpr<Arg>::operator()(long i) const & -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::operator()(long i) & -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class Arg>
        auto numpy_iexpr<Arg>::operator()(long i) &&
        -> decltype(std::move (*this)[i])
    {
      return std::move(*this)[i];
    }

    template <class Arg>
    numpy_gexpr<numpy_iexpr<Arg>, slice> numpy_iexpr<Arg>::
    operator()(slice const &s0) const
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg>
    numpy_gexpr<numpy_iexpr<Arg>, slice> numpy_iexpr<Arg>::
    operator[](slice const &s0) const
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg>
    numpy_gexpr<numpy_iexpr<Arg>, contiguous_slice> numpy_iexpr<Arg>::
    operator()(contiguous_slice const &s0) const
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg>
    numpy_gexpr<numpy_iexpr<Arg>, contiguous_slice> numpy_iexpr<Arg>::
    operator[](contiguous_slice const &s0) const
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg>
    template <class... S>
    numpy_gexpr<numpy_iexpr<Arg>, slice, S...> numpy_iexpr<Arg>::
    operator()(slice const &s0, S const &... s) const
    {
      return make_gexpr(*this, s0, s...);
    }

    template <class Arg>
    template <class... S>
    numpy_gexpr<numpy_iexpr<Arg>, contiguous_slice, S...> numpy_iexpr<Arg>::
    operator()(contiguous_slice const &s0, S const &... s) const
    {
      return make_gexpr(*this, s0, s...);
    }

    template <class Arg>
    template <class... S>
    auto numpy_iexpr<Arg>::operator()(long s0, S const &... s) const
        -> decltype(std::declval<numpy_iexpr<numpy_iexpr<Arg>>>()(s...))
    {
      return (*this)[s0](s...);
    }

    template <class Arg>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_iexpr<Arg>, F>>::type
    numpy_iexpr<Arg>::fast(F const &filter) const
    {
      return numpy_fexpr<numpy_iexpr, F>(*this, filter);
    }

    template <class Arg>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_iexpr<Arg>, F>>::type
        numpy_iexpr<Arg>::
        operator[](F const &filter) const
    {
      return fast(filter);
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype const &numpy_iexpr<Arg>::
    operator[](array<long, value> const &indices) const
    {
      size_t offset = indices[value - 1];
      long mult = _shape[value - 1];
      for (size_t i = value - 2; i > 0; --i) {
        offset += indices[i] * mult;
        mult *= _shape[i];
      }
      return buffer[offset + indices[0] * mult];
    }

    template <class Arg>
    typename numpy_iexpr<Arg>::dtype &numpy_iexpr<Arg>::
    operator[](array<long, value> const &indices)
    {
      return const_cast<dtype &>(
          const_cast<numpy_iexpr const &>(*this)[indices]);
    }

    template <class Arg>
    long numpy_iexpr<Arg>::flat_size() const
    {
      return std::accumulate(_shape.begin() + 1, _shape.end(), *_shape.begin(),
                             std::multiplies<long>());
    }

    template <class Arg>
    array<long, numpy_iexpr<Arg>::value> const &numpy_iexpr<Arg>::shape() const
    {
      return _shape;
    }

    template <class Arg>
    long numpy_iexpr<Arg>::buffer_offset(long index, utils::int_<0>)
    {
      return index;
    }

    template <class Arg>
    template <size_t N>
    long numpy_iexpr<Arg>::buffer_offset(long index, utils::int_<N>)
    {
      auto &&arg_shape = arg.shape();
      _shape[value - N] = arg_shape[value - N + 1];
      return buffer_offset(index * arg_shape[value - N + 1],
                           utils::int_<N - 1>());
    }

    template <class T, size_t N>
    numpy_iexpr<T> numpy_iexpr_helper<T, N>::get(T const &e, long i)
    {
      return {e, i};
    }

    template <class T>
    typename T::dtype numpy_iexpr_helper<T, 1>::get(T const &e, long i)
    {
      return e.buffer[i];
    }

    template <class T>
    typename T::dtype &numpy_iexpr_helper<T, 1>::get(T &&e, long i)
    {
      return e.buffer[i];
    }

    template <class T>
    typename T::dtype &numpy_iexpr_helper<T, 1>::get(T &e, long i)
    {
      return e.buffer[i];
    }
  }
}

#endif
