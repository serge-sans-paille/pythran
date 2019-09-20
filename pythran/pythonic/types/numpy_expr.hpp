#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/types/numpy_expr.hpp"

#include "pythonic/utils/meta.hpp"
#include "pythonic/types/nditerator.hpp"

#include "pythonic/__builtin__/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  namespace details
  {

    template <size_t value, class Args, size_t N, size_t... Is>
    struct all_valid_indices;

    template <size_t value, class Args, size_t... Is>
    struct all_valid_indices<value, Args, 0, Is...> {
      using type = utils::index_sequence<Is...>;
    };
    template <size_t value, class Args, size_t N, size_t... Is>
    struct all_valid_indices
        : std::conditional<(value <=
                            std::remove_reference<typename std::tuple_element<
                                N - 1, Args>::type>::type::value),
                           all_valid_indices<value, Args, N - 1, Is..., N - 1>,
                           all_valid_indices<value, Args, N - 1, Is...>>::type {
    };

    template <size_t value, class Args>
    using valid_indices =
        typename all_valid_indices<value, Args,
                                   std::tuple_size<Args>::value>::type;

    template <class V>
    long max_of(V v)
    {
      return v;
    }
    template <class V0, class V1, class... Vs>
    long max_of(V0 v0, V1 v1, Vs... vs)
    {
      return std::max((long)v0, max_of(v1, vs...));
    }

    template <size_t I, class Args, size_t... Is>
    long init_shape_element(Args const &args, utils::index_sequence<Is...>)
    {
      return max_of(std::get<I>(std::get<Is>(args).shape())...);
    }

    template <class pS, class Args, size_t... Is>
    pS init_shape(Args const &args, utils::index_sequence<Is...>)
    {
      return {init_shape_element<Is>(
          args, valid_indices<std::tuple_size<pS>::value, Args>{})...};
    }

    template <class pS, class Args>
    pS init_shape(Args const &args)
    {
      return init_shape<pS>(
          args, utils::make_index_sequence<std::tuple_size<pS>::value>());
    }
  }

  template <class Op, class... Args>
  numpy_expr<Op, Args...>::numpy_expr(Args const &... args)
      : args(args...), _shape(details::init_shape<shape_t>(this->args))
  {
  }

  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::const_iterator
      numpy_expr<Op, Args...>::_begin(utils::index_sequence<I...>) const
  {
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
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
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
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
        (same_shape &= (std::get<0>(std::get<I>(args).shape()) == size() ||
                        std::get<0>(std::get<I>(args).shape()) == 0))...};
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
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
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
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
            const_cast<typename std::decay<Args>::type &>(std::get<I>(args))
                .end()...};
  }

  template <class Op, class... Args>
  typename numpy_expr<Op, Args...>::iterator numpy_expr<Op, Args...>::end()
  {
    return _end(utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  auto numpy_expr<Op, Args...>::fast(long i) const
      -> decltype(this->_fast(i, utils::make_index_sequence<sizeof...(Args)>{}))
  {
    return _fast(i, utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  template <class... Indices>
  auto numpy_expr<Op, Args...>::map_fast(Indices... indices) const -> decltype(
      this->_map_fast(array<long, sizeof...(Indices)>{{indices...}},
                      utils::make_index_sequence<sizeof...(Args)>{}))
  {
    static_assert(sizeof...(Indices) == sizeof...(Args), "compatible call");
    return _map_fast(array<long, sizeof...(Indices)>{{indices...}},
                     utils::make_index_sequence<sizeof...(Args)>{});
  }

  template <class Op, class... Args>
  auto numpy_expr<Op, Args...>::operator[](long i) const
      -> decltype(this->fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
    return fast(i);
  }

#ifdef USE_XSIMD
  template <class Op, class... Args>
  template <size_t... I>
  typename numpy_expr<Op, Args...>::simd_iterator
      numpy_expr<Op, Args...>::_vbegin(vectorize,
                                       utils::index_sequence<I...>) const
  {
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
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
    return {{make_step(std::get<0>(_shape),
                       std::get<0>(std::get<I>(args).shape()))...},
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
  template <class S0, class... S>
  auto numpy_expr<Op, Args...>::operator()(S0 const &s0, S const &... s) const
      -> typename std::enable_if<
          !std::is_scalar<S0>::value || sizeof...(S) != 0,
          decltype(this->_get(utils::make_index_sequence<sizeof...(Args)>{}, s0,
                              s...))>::type
  {
    return _get(utils::make_index_sequence<sizeof...(Args)>{}, s0, s...);
  }

  template <class Op, class... Args>
  template <class F>
  typename std::enable_if<
      is_numexpr_arg<F>::value &&
          std::is_same<bool, typename F::dtype>::value &&
          !is_pod_array<F>::value,
      numpy_vexpr<numpy_expr<Op, Args...>, ndarray<long, pshape<long>>>>::type
  numpy_expr<Op, Args...>::fast(F const &filter) const
  {
    long sz = std::get<0>(filter.shape());
    long *raw = (long *)malloc(sz * sizeof(long));
    long n = 0;
    for (long i = 0; i < sz; ++i)
      if (filter.fast(i))
        raw[n++] = i;
    // realloc(raw, n * sizeof(long));
    long shp[1] = {n};
    return this->fast(
        ndarray<long, pshape<long>>(raw, shp, types::ownership::owned));
  }

  template <class Op, class... Args>
  template <class F>
  typename std::enable_if<
      is_numexpr_arg<F>::value &&
          std::is_same<bool, typename F::dtype>::value &&
          !is_pod_array<F>::value,
      numpy_vexpr<numpy_expr<Op, Args...>, ndarray<long, pshape<long>>>>::type
      numpy_expr<Op, Args...>::
      operator[](F const &filter) const
  {
    return fast(filter);
  }
  template <class Op, class... Args>
  template <class F> // indexing through an array of indices -- a view
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              !is_array_index<F>::value &&
                              !std::is_same<bool, typename F::dtype>::value &&
                              !is_pod_array<F>::value,
                          numpy_vexpr<numpy_expr<Op, Args...>, F>>::type
      numpy_expr<Op, Args...>::
      operator[](F const &filter) const
  {
    return {*this, filter};
  }

  template <class Op, class... Args>
  template <class F> // indexing through an array of indices -- a view
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              !is_array_index<F>::value &&
                              !std::is_same<bool, typename F::dtype>::value &&
                              !is_pod_array<F>::value,
                          numpy_vexpr<numpy_expr<Op, Args...>, F>>::type
  numpy_expr<Op, Args...>::fast(F const &filter) const
  {
    return {*this, filter};
  }

  template <class Op, class... Args>
  numpy_expr<Op, Args...>::operator bool() const
  {
    if (sutils::any_of(_shape, [](long n) { return n != 1; }))
      throw ValueError("The truth value of an array with more than one element "
                       "is ambiguous. Use a.any() or a.all()");
    array<long, value> first = {0};
    return operator[](first);
  }

  template <class Op, class... Args>
  long numpy_expr<Op, Args...>::flat_size() const
  {
    return sutils::prod(_shape);
  }

  template <class Op, class... Args>
  long numpy_expr<Op, Args...>::size() const
  {
    return std::get<0>(_shape);
  }
}
PYTHONIC_NS_END

#endif
