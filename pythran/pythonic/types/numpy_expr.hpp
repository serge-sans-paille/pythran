#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/types/numpy_expr.hpp"

#include "pythonic/utils/meta.hpp"
#include "pythonic/types/nditerator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  namespace details
  {

    template <size_t value, class... Args>
    array<long, value> init_shape(Args const &... args)
    {
      array<long, value> shape;
      for (size_t i = 0; i < value; ++i) {
        long max = 0;
        std::initializer_list<long> _{
            (value <= std::remove_reference<Args>::type::value &&
                     args.shape()[i] > max
                 ? max = args.shape()[i]
                 : max)...};
        shape[i] = max;
      }
      return shape;
    }
  }

  template <class Op, class... Args>
  numpy_expr<Op, Args...>::numpy_expr(Args const &... args)
      : args(args...), _shape(details::init_shape<value>(args...))
  {
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::const_iterator
      numpy_expr<Op, Args...>::_begin(utils::index_sequence<I...>) const
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            const_cast<typename std::decay<Args>::type const &>(
                std::get<I>(args)).begin()...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::const_iterator
  numpy_expr<Op, Args...>::begin() const
  {
    return _begin(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::const_iterator
      numpy_expr<Op, Args...>::_end(utils::index_sequence<I...>) const
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            const_cast<typename std::decay<Args>::type const &>(
                std::get<I>(args)).end()...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::const_iterator
  numpy_expr<Op, Args...>::end() const
  {
    return _end(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::const_fast_iterator
      numpy_expr<Op, Args...>::begin(types::fast) const
  {
    return {*this, 0};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::const_fast_iterator
      numpy_expr<Op, Args...>::end(types::fast) const
  {
    return {*this, size()};
  }

  template <class Op, class... Args>
  template <size_t... I>
  bool numpy_expr<Op, Args...>::_no_broadcast(utils::index_sequence<I...>) const
  {
    bool child_broadcast = false;
    std::initializer_list<bool> _0 = {
        (child_broadcast |= !utils::no_broadcast(std::get<I>(args)))...};
    if (child_broadcast)
      return false;

    bool same_shape = true;
    std::initializer_list<bool> _1 = {
        (same_shape &= (std::get<I>(args).shape()[0] == size() ||
                        std::get<I>(args).shape()[0] == 0))...};
    return same_shape;
  }
  template <class Op, class... Args>
  bool numpy_expr<Op, Args...>::no_broadcast() const
  {
    return _no_broadcast(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::iterator
      numpy_expr<Op, Args...>::_begin(utils::index_sequence<I...>)
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            const_cast<typename std::decay<Args>::type &>(std::get<I>(args))
                .begin()...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::iterator numpy_expr<Op, Args...>::begin()
  {
    return _begin(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::iterator
      numpy_expr<Op, Args...>::_end(utils::index_sequence<I...>)
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            const_cast<typename std::decay<Args>::type &>(std::get<I>(args))
                .end()...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::iterator numpy_expr<Op, Args...>::end()
  {
    return _end(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  auto numpy_expr<Op, Args...>::_fast(long i, utils::index_sequence<I...>) const
      -> decltype(Op()(std::get<I>(args).fast(i)...))
  {
    return Op()(std::get<I>(args).fast(i)...);
  }

  template <class Op, class... Args>
  auto numpy_expr<Op, Args...>::fast(long i) const
      -> decltype(this->_fast(i, utils::make_index_sequence<sizeof...(Args)>{}))
  {
    return _fast(i, utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  auto numpy_expr<Op, Args...>::_map_fast(
      std::array<long, sizeof...(I)> const &indices,
      utils::index_sequence<I...>) const
      -> decltype(Op()(std::get<I>(args).fast(std::get<I>(indices))...))
  {
    return Op()(std::get<I>(args).fast(std::get<I>(indices))...);
  }

  template <class Op, class... Args>
  template <class... Indices>
  auto numpy_expr<Op, Args...>::map_fast(Indices... indices) const -> decltype(
      this->_map_fast(std::array<long, sizeof...(Indices)>{{indices...}},
                      utils::make_index_sequence<sizeof...(Args)>{}))
  {
    static_assert(sizeof...(Indices) == sizeof...(Args), "compatible call");
    return _map_fast(std::array<long, sizeof...(Indices)>{{indices...}},
                     utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  auto numpy_expr<Op, Args...>::operator[](long i) const
      -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

#ifdef USE_BOOST_SIMD
  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::simd_iterator
      numpy_expr<Op, Args...>::_vbegin(vectorize,
                                       utils::index_sequence<I...>) const
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            std::make_tuple(const_cast<typename std::decay<Args>::type const &>(
                                std::get<I>(args)).begin()...),
            std::get<I>(args).vbegin(vectorize{})...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::simd_iterator
      numpy_expr<Op, Args...>::vbegin(vectorize) const
  {
    return _vbegin(vectorize{}, utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::simd_iterator
      numpy_expr<Op, Args...>::_vend(vectorize,
                                     utils::index_sequence<I...>) const
  {
    return {{(size() == std::get<I>(args).shape()[0])...},
            std::make_tuple(const_cast<typename std::decay<Args>::type const &>(
                                std::get<I>(args)).end()...),
            std::get<I>(args).vend(vectorize{})...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::simd_iterator
      numpy_expr<Op, Args...>::vend(vectorize) const
  {
    return _vend(vectorize{}, utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::simd_iterator_nobroadcast
      numpy_expr<Op, Args...>::_vbegin(vectorize_nobroadcast,
                                       utils::index_sequence<I...>) const
  {
    return {std::get<I>(args).vbegin(vectorize_nobroadcast{})...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::simd_iterator_nobroadcast
      numpy_expr<Op, Args...>::vbegin(vectorize_nobroadcast) const
  {
    return _vbegin(vectorize_nobroadcast{},
                   utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::simd_iterator_nobroadcast
      numpy_expr<Op, Args...>::_vend(vectorize_nobroadcast,
                                     utils::index_sequence<I...>) const
  {
    return {std::get<I>(args).vend(vectorize_nobroadcast{})...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::simd_iterator_nobroadcast
      numpy_expr<Op, Args...>::vend(vectorize_nobroadcast) const
  {
    return _vend(vectorize_nobroadcast{},
                 utils::make_index_sequence<sizeof...(Args)>{});
  }

#endif

  template <class Op, class... Args>
  template <size_t... I, class... S>
  auto numpy_expr<Op, Args...>::_get(utils::index_sequence<I...>,
                                     S const &... s) const
      -> decltype(Op{}(std::get<I>(args)(s...)...))
  {
    return Op{}(std::get<I>(args)(s...)...);
  }

  template <class Op, class... Args>
  template <class S0, class... S>
  auto numpy_expr<Op, Args...>::operator()(S0 const &s0, S const &... s) const
      -> typename std::enable_if<
          !std::is_scalar<S0>::value,
          decltype(this->_get(utils::make_index_sequence<sizeof...(Args)>{}, s0,
                              s...))>::type
  {
    return _get(utils::make_index_sequence<sizeof...(Args)>{}, s0, s...);
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
  long numpy_expr<Op, Args...>::flat_size() const
  {
    return std::accumulate(_shape.begin() + 1, _shape.end(), _shape.front(),
                           std::multiplies<long>());
  }

  template <class Op, class... Args>
  long numpy_expr<Op, Args...>::size() const
  {
    return _shape[0];
  }
}
PYTHONIC_NS_END

#endif
