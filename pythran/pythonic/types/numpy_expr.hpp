#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/types/numpy_expr.hpp"

#include "pythonic/utils/meta.hpp"

namespace pythonic
{

  namespace types
  {

    template <class Op, class... Args>
    numpy_expr<Op, Args...>::numpy_expr()
    {
    }

    template <class Op, class... Args>
    numpy_expr<Op, Args...>::numpy_expr(Args const &... args)
        : args(args...),
          _shape(std::get<utils::max_element<Args::value...>::index>(this->args)
                     .shape())
    {
    }

    template <class Op, class... Args>
    typename numpy_expr<Op, Args...>::iterator
    numpy_expr<Op, Args...>::begin() const
    {
      return {*this, 0};
    }

    template <class Op, class... Args>
    typename numpy_expr<Op, Args...>::iterator
    numpy_expr<Op, Args...>::end() const
    {
      return {*this, _shape[0]};
    }

    template <class Op, class... Args>
    template <int... I>
    auto numpy_expr<Op, Args...>::_fast(long i, utils::seq<I...>) const
        -> decltype(Op()(std::get<I>(args).fast(i)...))
    {
      return Op()(std::get<I>(args).fast(i)...); // FIXME: broadcasting can be
                                                 // achieved here through a
                                                 // modulus, but that's terribly
                                                 // costly
    }

    template <class Op, class... Args>
    auto numpy_expr<Op, Args...>::fast(long i) const
        -> decltype(this->_fast(i,
                                typename utils::gens<sizeof...(Args)>::type{}))
    {
      return _fast(i, typename utils::gens<sizeof...(Args)>::type{});
    }

    template <class Op, class... Args>
    auto numpy_expr<Op, Args...>::operator[](long i) const
        -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Op, class... Args>
    auto numpy_expr<Op, Args...>::operator()(long i) const
        -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Op, class... Args>
    array<long, numpy_expr<Op, Args...>::value> const &
    numpy_expr<Op, Args...>::shape() const
    {
      return _shape;
    }

#ifdef USE_BOOST_SIMD
    template <class Op, class... Args>
    template <int... I>
    auto numpy_expr<Op, Args...>::_load(long i, utils::seq<I...>) const
        -> decltype(Op()(std::get<I>(args).load(i)...))
    {
      return Op()(std::get<I>(args).load(i)...);
    }

    template <class Op, class... Args>
    template <class I> // template to prevent automatic instantiation when the
    // type is not vectorizable
    auto numpy_expr<Op, Args...>::load(I i) const
        -> decltype(this->_load(i,
                                typename utils::gens<sizeof...(Args)>::type{}))
    {
      return _load(i, typename utils::gens<sizeof...(Args)>::type{});
    }
#endif

    template <class Op, class... Args>
    template <int... I, class... S>
    auto numpy_expr<Op, Args...>::_get(utils::seq<I...>, S const &... s) const
        -> decltype(Op{}(std::get<I>(args)(s...)...))
    {
      return Op{}(std::get<I>(args)(s...)...);
    }

    template <class Op, class... Args>
    template <class S0, class... S>
    auto numpy_expr<Op, Args...>::operator()(S0 const &s0, S const &... s) const
        -> typename std::enable_if<
            not std::is_scalar<S0>::value,
            decltype(this->_get(typename utils::gens<sizeof...(Args)>::type{},
                                s0, s...))>::type
    {
      return _get(typename utils::gens<sizeof...(Args)>::type{}, s0, s...);
    }

    template <class Op, class... Args>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_expr<Op, Args...>, F>>::type
    numpy_expr<Op, Args...>::fast(F const &filter) const
    {
      return numpy_fexpr<numpy_expr, F>(*this, filter);
    }

    template <class Op, class... Args>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_expr<Op, Args...>, F>>::type
        numpy_expr<Op, Args...>::
        operator[](F const &filter) const
    {
      return fast(filter);
    }

    template <class Op, class... Args>
    template <int... I>
    long numpy_expr<Op, Args...>::_flat_size(utils::seq<I...>) const
    {
      long const sizes[] = {std::get<I>(args).flat_size()...};
      return *std::max_element(std::begin(sizes), std::end(sizes));
    }

    template <class Op, class... Args>
    long numpy_expr<Op, Args...>::flat_size() const
    {
      return _flat_size(typename utils::gens<sizeof...(Args)>::type{});
    }

    template <class Op, class... Args>
    long numpy_expr<Op, Args...>::size() const
    {
      return _shape[0];
    }
  }
}

#endif
