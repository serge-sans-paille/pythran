#ifndef PYTHONIC_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_TEXPR_HPP

#include "pythonic/include/types/numpy_texpr.hpp"

#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace types
  {

    template <class E>
    array<long, 2> const &numpy_texpr_2<E>::shape() const
    {
      return _shape;
    }

    template <class E>
    numpy_texpr_2<E>::numpy_texpr_2()
    {
    }

    template <class E>
    numpy_texpr_2<E>::numpy_texpr_2(Arg const &arg)
        : arg(arg), _shape{{arg.shape()[1], arg.shape()[0]}}
    {
    }

    template <class E>
    typename numpy_texpr_2<E>::const_iterator numpy_texpr_2<E>::begin() const
    {
      return {*this, 0};
    }

    template <class E>
    typename numpy_texpr_2<E>::const_iterator numpy_texpr_2<E>::end() const
    {
      return {*this, _shape[0]};
    }

    template <class E>
    typename numpy_texpr_2<E>::iterator numpy_texpr_2<E>::begin()
    {
      return {*this, 0};
    }

    template <class E>
    typename numpy_texpr_2<E>::iterator numpy_texpr_2<E>::end()
    {
      return {*this, _shape[0]};
    }

    template <class E>
    auto numpy_texpr_2<E>::fast(long i) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              i))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 i);
    }

    template <class E>
    auto numpy_texpr_2<E>::fast(long i)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              i))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 i);
    }

#ifdef USE_BOOST_SIMD
    template <class E>
    typename numpy_texpr_2<E>::simd_iterator numpy_texpr_2<E>::vbegin() const
    {
      return {*this, 0};
    }

    template <class E>
    typename numpy_texpr_2<E>::simd_iterator numpy_texpr_2<E>::vend() const
    {
      return {*this, 0}; // not vectorizable anyway
    }
    template <class E>
    template <class I>
    void numpy_texpr_2<E>::load(I) const
    {
      static_assert(I::this_should_never_happen, "this is *not* vectorizable");
    }
#endif

    template <class E>
    auto numpy_texpr_2<E>::operator[](long i) const -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator[](long i) -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(long i) const -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(long i) -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class E>
    auto numpy_texpr_2<E>::
    operator[](array<long, numpy_texpr_2<E>::value> const &indices)
        -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}])
    {
      return arg[array<long, 2>{{indices[1], indices[0]}}];
    }

    template <class E>
    auto numpy_texpr_2<E>::
    operator[](array<long, numpy_texpr_2<E>::value> const &indices) const
        -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}])
    {
      return arg[array<long, 2>{{indices[1], indices[0]}}];
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(contiguous_slice const &s0) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(contiguous_slice const &s0)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(slice const &s0) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator()(slice const &s0)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0))
    {
      return arg(contiguous_slice(pythonic::__builtin__::None,
                                  pythonic::__builtin__::None),
                 s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator[](contiguous_slice const &s0) const
        -> decltype(this->operator()(s0))
    {
      return (*this)(s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator[](contiguous_slice const &s0)
        -> decltype(this->operator()(s0))
    {
      return (*this)(s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator[](slice const &s0) const
        -> decltype(this->operator()(s0))
    {
      return (*this)(s0);
    }

    template <class E>
    auto numpy_texpr_2<E>::operator[](slice const &s0)
        -> decltype(this->operator()(s0))
    {
      return (*this)(s0);
    }

    /* element filtering */
    template <class E>
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value and
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_texpr_2<E>, F>>::type
    numpy_texpr_2<E>::fast(F const &filter) const
    {
      return {*this, filter};
    }

    template <class E>
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value and
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_texpr_2<E>, F>>::type
        numpy_texpr_2<E>::
        operator[](F const &filter) const
    {
      return fast(filter);
    }

    template <class E>
    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value and
            not std::is_same<bool, typename F::dtype>::value,
        ndarray<typename numpy_texpr_2<E>::dtype, 2>>::type numpy_texpr_2<E>::
    operator[](F const &filter) const
    {
      ndarray<typename numpy_texpr_2<E>::dtype, 2> out(
          array<long, 2>{{filter.flat_size(), shape()[1]}}, none_type());
      std::transform(
          filter.begin(), filter.end(), out.begin(),
          [this](typename F::dtype index) { return operator[](index); });
      return out;
    }

    template <class E>
    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value and
            not std::is_same<bool, typename F::dtype>::value,
        ndarray<typename numpy_texpr_2<E>::dtype, 2>>::type
    numpy_texpr_2<E>::fast(F const &filter) const
    {
      ndarray<typename numpy_texpr_2<E>::dtype, 2> out(
          array<long, 2>{{filter.flat_size(), shape()[1]}}, none_type());
      std::transform(filter.begin(), filter.end(), out.begin(),
                     [this](typename F::dtype index) { return fast(index); });
      return out;
    }

    template <class E>
    template <class S, int... I>
    auto numpy_texpr_2<E>::_reverse_index(S const &indices,
                                          utils::seq<I...>) const
        -> decltype(this->arg(std::get<I>(indices)...))
    {
      return arg(std::get<I>(indices)...);
    }

    template <class E>
    template <class S0, class... S>
    auto numpy_texpr_2<E>::operator()(S0 const &s0, S const &... s) const
        -> decltype(this->_reverse_index(
            std::tuple<S0 const &, S const &...>{s0, s...},
            typename utils::rgens<1 + sizeof...(S)>::type{}))
    {
      return _reverse_index(std::tuple<S0 const &, S const &...>{s0, s...},
                            typename utils::rgens<1 + sizeof...(S)>::type{});
    }

    template <class E>
    long numpy_texpr_2<E>::flat_size() const
    {
      return arg.flat_size();
    }

    template <class E>
    intptr_t numpy_texpr_2<E>::id() const
    {
      return arg.id();
    }

    template <class E>
    ndarray<typename numpy_texpr_2<E>::dtype, numpy_texpr_2<E>::value>
    numpy_texpr_2<E>::copy() const
    {
      return *this;
    }

    // only implemented for N = 2
    template <class T>
    numpy_texpr<ndarray<T, 2>>::numpy_texpr()
    {
    }

    template <class T>
    numpy_texpr<ndarray<T, 2>>::numpy_texpr(ndarray<T, 2> const &arg)
        : numpy_texpr_2<ndarray<T, 2>>{arg}
    {
    }

    template <class E, class... S>
    numpy_texpr<numpy_gexpr<E, S...>>::numpy_texpr()
    {
    }

    template <class E, class... S>
    numpy_texpr<numpy_gexpr<E, S...>>::numpy_texpr(
        numpy_gexpr<E, S...> const &arg)
        : numpy_texpr_2<numpy_gexpr<E, S...>>{arg}
    {
    }
  }
}

#endif
