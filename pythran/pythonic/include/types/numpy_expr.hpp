#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/types/nditerator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class... Tys>
  struct count_non_integral;
  template <>
  struct count_non_integral<long> : std::integral_constant<long, 1> {
  };
  template <class T>
  struct count_non_integral<T> : std::integral_constant<long, 0> {
  };
  template <class Ty0, class Ty1, class... Tys>
  struct count_non_integral<Ty0, Ty1, Tys...>
      : std::integral_constant<long,
                               count_non_integral<Ty0>::value +
                                   count_non_integral<Ty1, Tys...>::value> {
  };
  template <class P>
  struct is_perfect_stepping;
  template <class... Tys>
  struct is_perfect_stepping<pshape<Tys...>>
      : std::integral_constant<bool, count_non_integral<Tys...>::value == 1> {
  };

  template <class Expr>
  struct is_numexpr_arg;

  template <class Expr, class... Slice>
  struct numpy_gexpr;

  template <class Op>
  struct Dereferencer {
    template <class Ts, size_t... I>
    auto operator()(Ts const &iters, utils::index_sequence<I...>)
        -> decltype(Op{}(*std::get<I>(iters)...))
    {
      return Op{}(*std::get<I>(iters)...);
    }
  };
  template <class T>
  struct step {
    using type = typename T::step_type;
  };

  template <class Op, class Steps, class... Iters>
  struct numpy_expr_iterator
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<decltype(std::declval<
                          Op>()(*std::declval<Iters>()...))>::type> {
    Steps steps_;
    std::tuple<Iters...> iters_;

    numpy_expr_iterator(array<long, sizeof...(Iters)> steps, Iters... iters)
        : steps_(steps), iters_(iters...)
    {
    }

    numpy_expr_iterator(numpy_expr_iterator const &other)
        : steps_(other.steps_), iters_(other.iters_)
    {
    }

    numpy_expr_iterator &operator=(numpy_expr_iterator const &other)
    {
      iters_ = other.iters_;
      return *this;
    }

    template <size_t... I>
    auto _dereference(utils::index_sequence<I...> s) const
        -> decltype(Dereferencer<Op>{}(iters_, s))
    {
      return Dereferencer<Op>{}(iters_, s);
    }

    auto operator*() const -> decltype(
        this->_dereference(utils::make_index_sequence<sizeof...(Iters)>{}))
    {
      return _dereference(utils::make_index_sequence<sizeof...(Iters)>{});
    }

    template <size_t I>
    bool _incr_opt(std::integral_constant<bool, true> long_step)
    {
      if (is_perfect_stepping<Steps>::value) {
        ++std::get<I>(iters_);
      } else {
        std::get<I>(iters_) += std::get<I>(steps_);
      }
      return true;
    }

    template <size_t I>
    bool _incr_opt(std::integral_constant<bool, false> long_step)
    {
      if (std::tuple_element<I, Steps>::type::value)
        ++std::get<I>(iters_);
      return true;
    }

    template <size_t... I>
    void _incr(utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{_incr_opt<I>(std::integral_constant<
          bool, std::is_same<long, typename std::tuple_element<
                                       I, Steps>::type>::value>{})...};
    }
    numpy_expr_iterator &operator++()
    {
      _incr(utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    numpy_expr_iterator operator+(long i) const
    {
      numpy_expr_iterator other(*this);
      return other += i;
    }

    template <size_t... I>
    void _update(long i, utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{
          (std::get<I>(iters_) += std::get<I>(steps_) * i, true)...};
    }
    numpy_expr_iterator &operator+=(long i)
    {
      _update(i, utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    template <size_t... I>
    long _difference(numpy_expr_iterator const &other,
                     utils::index_sequence<I...>) const
    {
      std::initializer_list<long> distances{(static_cast<long>(
          std::get<I>(iters_) - std::get<I>(other.iters_)))...};
      return *std::max_element(distances.begin(), distances.end());
    }

    long operator-(numpy_expr_iterator const &other) const
    {
      return _difference(other, utils::make_index_sequence<sizeof...(Iters)>{});
    }

    bool _neq(numpy_expr_iterator const &other, utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _neq(numpy_expr_iterator const &other, utils::int_<I>) const
    {
      return (std::get<I - 1>(steps_) &&
              (std::get<I - 1>(iters_) != std::get<I - 1>(other.iters_))) ||
             _neq(other, utils::int_<I - 1>{});
    }

    bool operator!=(numpy_expr_iterator const &other) const
    {
      return _neq(other, utils::int_<sizeof...(Iters)>{});
    }
    bool _eq(numpy_expr_iterator const &other, utils::int_<0u>) const
    {
      return true;
    }

    template <size_t I>
    bool _eq(numpy_expr_iterator const &other, utils::int_<I>) const
    {
      return (!std::get<I - 1>(steps_) ||
              (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_))) &&
             _eq(other, utils::int_<I - 1>{});
    }

    bool operator==(numpy_expr_iterator const &other) const
    {
      return _eq(other, utils::int_<sizeof...(Iters)>{});
    }

    bool _lt(numpy_expr_iterator const &other, utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _lt(numpy_expr_iterator const &other, utils::int_<I>) const
    {
      if (!std::get<I - 1>(steps_) ||
          (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_)))
        return _lt(other, utils::int_<I - 1>{});
      else
        return std::get<I - 1>(steps_) &&
               (std::get<I - 1>(iters_) < std::get<I - 1>(other.iters_));
    }

    bool operator<(numpy_expr_iterator const &other) const
    {
      return _lt(other, utils::int_<sizeof...(Iters)>{});
    }
  };
#ifdef USE_XSIMD
  template <class E, class Op, class Steps, class SIters, class... Iters>
  struct numpy_expr_simd_iterator
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<decltype(std::declval<
                          Op>()(*std::declval<Iters>()...))>::type> {
    Steps steps_;
    std::tuple<Iters...> iters_;
    SIters siters_;

    numpy_expr_simd_iterator(array<long, sizeof...(Iters)> steps,
                             SIters const &siters, Iters... iters)
        : steps_(steps), iters_(iters...), siters_(siters)
    {
    }

    numpy_expr_simd_iterator(numpy_expr_simd_iterator const &other)
        : steps_(other.steps_), iters_(other.iters_), siters_(other.siters_)
    {
    }

    numpy_expr_simd_iterator &operator=(numpy_expr_simd_iterator const &other)
    {
      iters_ = other.iters_;
      siters_ = other.siters_;
      return *this;
    }

    template <size_t... I>
    auto _dereference(utils::index_sequence<I...>) const
        -> decltype(Op{}(*std::get<I>(iters_)...))
    {
      return Op{}(((std::get<I>(steps_))
                       ? (*std::get<I>(iters_))
                       : (xsimd::simd_type<decltype(*std::get<I>(iters_))>(
                             *std::get<I>(siters_))))...);
    }

    auto operator*() const -> decltype(
        this->_dereference(utils::make_index_sequence<sizeof...(Iters)>{}))
    {
      return _dereference(utils::make_index_sequence<sizeof...(Iters)>{});
    }

    template <size_t I>
    bool _incr_opt(std::integral_constant<bool, true> long_step)
    {
      if (is_perfect_stepping<Steps>::value)
        ++std::get<I>(iters_);
      else
        std::get<I>(iters_) += std::get<I>(steps_);
      return true;
    }

    template <size_t I>
    bool _incr_opt(std::integral_constant<bool, false> long_step)
    {
      if (std::tuple_element<I, Steps>::type::value)
        ++std::get<I>(iters_);
      return true;
    }

    template <size_t... I>
    void _incr(utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{_incr_opt<I>(std::integral_constant<
          bool, std::is_same<long, typename std::tuple_element<
                                       I, Steps>::type>::value>{})...};
    }
    numpy_expr_simd_iterator &operator++()
    {
      _incr(utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    numpy_expr_simd_iterator operator+(long i) const
    {
      numpy_expr_simd_iterator other(*this);
      return other += i;
    }

    template <size_t... I>
    void _update(long i, utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{
          (std::get<I>(iters_) += std::get<I>(steps_) * i, true)...};
    }
    numpy_expr_simd_iterator &operator+=(long i)
    {
      _update(i, utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    template <size_t... I>
    long _difference(numpy_expr_simd_iterator const &other,
                     utils::index_sequence<I...>) const
    {
      std::initializer_list<long> distances{
          (std::get<I>(iters_) - std::get<I>(other.iters_))...};
      return *std::max_element(distances.begin(), distances.end());
    }

    long operator-(numpy_expr_simd_iterator const &other) const
    {
      return _difference(other, utils::make_index_sequence<sizeof...(Iters)>{});
    }

    bool _neq(numpy_expr_simd_iterator const &other, utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _neq(numpy_expr_simd_iterator const &other, utils::int_<I>) const
    {
      return (std::get<I - 1>(steps_) &&
              (std::get<I - 1>(iters_) != std::get<I - 1>(other.iters_))) ||
             _neq(other, utils::int_<I - 1>{});
    }

    bool operator!=(numpy_expr_simd_iterator const &other) const
    {
      return _neq(other, utils::int_<sizeof...(Iters)>{});
    }

    bool _eq(numpy_expr_simd_iterator const &other, utils::int_<0u>) const
    {
      return true;
    }

    template <size_t I>
    bool _eq(numpy_expr_simd_iterator const &other, utils::int_<I>) const
    {
      return (std::get<I - 1>(steps_) &&
              (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_))) &&
             _eq(other, utils::int_<I - 1>{});
    }

    bool operator==(numpy_expr_simd_iterator const &other) const
    {
      return _eq(other, utils::int_<sizeof...(Iters)>{});
    }

    bool _lt(numpy_expr_simd_iterator const &other, utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _lt(numpy_expr_simd_iterator const &other, utils::int_<I>) const
    {
      if (std::get<I - 1>(steps_) &&
          (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_)))
        return _lt(other, utils::int_<I - 1>{});
      else
        return std::get<I - 1>(steps_) &&
               (std::get<I - 1>(iters_) < std::get<I - 1>(other.iters_));
    }

    bool operator<(numpy_expr_simd_iterator const &other) const
    {
      return _lt(other, utils::int_<sizeof...(Iters)>{});
    }
  };

  template <class E, class Op, class... Iters>
  struct numpy_expr_simd_iterator_nobroadcast
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<decltype(std::declval<
                          Op>()(*std::declval<Iters>()...))>::type> {
    std::tuple<Iters...> iters_;

    numpy_expr_simd_iterator_nobroadcast(Iters... iters) : iters_(iters...)
    {
    }

    numpy_expr_simd_iterator_nobroadcast(
        numpy_expr_simd_iterator_nobroadcast const &other)
        : iters_(other.iters_)
    {
    }

    numpy_expr_simd_iterator_nobroadcast &
    operator=(numpy_expr_simd_iterator_nobroadcast const &other)
    {
      iters_ = other.iters_;
      return *this;
    }

    template <size_t... I>
    auto _dereference(utils::index_sequence<I...>) const
        -> decltype(Op{}(*std::get<I>(iters_)...))
    {
      return Op{}((*std::get<I>(iters_))...);
    }

    auto operator*() const -> decltype(
        this->_dereference(utils::make_index_sequence<sizeof...(Iters)>{}))
    {
      return _dereference(utils::make_index_sequence<sizeof...(Iters)>{});
    }

    template <size_t... I>
    void _incr(utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{(++std::get<I>(iters_), true)...};
    }
    numpy_expr_simd_iterator_nobroadcast &operator++()
    {
      _incr(utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    template <size_t... I>
    long _difference(numpy_expr_simd_iterator_nobroadcast const &other,
                     utils::index_sequence<I...>) const
    {
      std::initializer_list<long> distances{
          (std::get<I>(iters_) - std::get<I>(other.iters_))...};
      return *std::max_element(distances.begin(), distances.end());
    }

    long operator-(numpy_expr_simd_iterator_nobroadcast const &other) const
    {
      return _difference(other, utils::make_index_sequence<sizeof...(Iters)>{});
    }

    numpy_expr_simd_iterator_nobroadcast operator+(long i) const
    {
      numpy_expr_simd_iterator_nobroadcast other(*this);
      return other += i;
    }

    template <size_t... I>
    void _update(long i, utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{(std::get<I>(iters_) += i, true)...};
    }
    numpy_expr_simd_iterator_nobroadcast &operator+=(long i)
    {
      _update(i, utils::make_index_sequence<sizeof...(Iters)>{});
      return *this;
    }

    bool _neq(numpy_expr_simd_iterator_nobroadcast const &other,
              utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _neq(numpy_expr_simd_iterator_nobroadcast const &other,
              utils::int_<I>) const
    {
      return (std::get<I - 1>(iters_) != std::get<I - 1>(other.iters_)) ||
             _neq(other, utils::int_<I - 1>{});
    }

    bool operator!=(numpy_expr_simd_iterator_nobroadcast const &other) const
    {
      return _neq(other, utils::int_<sizeof...(Iters)>{});
    }

    bool _eq(numpy_expr_simd_iterator_nobroadcast const &other,
             utils::int_<0u>) const
    {
      return true;
    }

    template <size_t I>
    bool _eq(numpy_expr_simd_iterator_nobroadcast const &other,
             utils::int_<I>) const
    {
      return (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_)) &&
             _eq(other, utils::int_<I - 1>{});
    }

    bool operator==(numpy_expr_simd_iterator_nobroadcast const &other) const
    {
      return _eq(other, utils::int_<sizeof...(Iters)>{});
    }

    bool _lt(numpy_expr_simd_iterator_nobroadcast const &other,
             utils::int_<0u>) const
    {
      return false;
    }

    template <size_t I>
    bool _lt(numpy_expr_simd_iterator_nobroadcast const &other,
             utils::int_<I>) const
    {
      if (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_))
        return _lt(other, utils::int_<I - 1>{});
      else
        return std::get<I - 1>(iters_) < std::get<I - 1>(other.iters_);
    }

    bool operator<(numpy_expr_simd_iterator_nobroadcast const &other) const
    {
      return _lt(other, utils::int_<sizeof...(Iters)>{});
    }
  };
#endif

  template <class T>
  struct integral_value : std::integral_constant<long, 0> {
  };
  template <long N>
  struct integral_value<std::integral_constant<long, N>>
      : std::integral_constant<long, (N == 1 ? 0 : 1)> {
  };

  template <class T>
  using step_type_t = typename std::conditional<
      std::is_same<long, typename std::tuple_element<
                             0, typename T::shape_t>::type>::value,
      long, std::integral_constant<
                long, integral_value<typename std::tuple_element<
                          0, typename T::shape_t>::type>::value>>::type;

  /* Expression template for numpy expressions - binary operators
   */
  template <class Op, class... Args>
  struct numpy_expr {
    using first_arg = typename utils::front<Args...>::type;
    static const bool is_vectorizable =
        utils::all_of<
            std::remove_reference<Args>::type::is_vectorizable...>::value &&
        utils::all_of<
            std::is_same<typename std::remove_cv<typename std::remove_reference<
                             first_arg>::type>::type::dtype,
                         typename std::remove_cv<typename std::remove_reference<
                             Args>::type>::type::dtype>::value...>::value &&
        types::is_vector_op<
            Op, typename std::remove_reference<Args>::type::dtype...>::value;
    static const bool is_strided =
        utils::any_of<std::remove_reference<Args>::type::is_strided...>::value;
    using const_iterator = numpy_expr_iterator<
        Op, pshape<step_type_t<typename std::remove_reference<Args>::type>...>,
        typename std::remove_reference<Args>::type::const_iterator...>;
    using iterator = numpy_expr_iterator<
        Op, pshape<step_type_t<typename std::remove_reference<Args>::type>...>,
        typename std::remove_reference<Args>::type::iterator...>;
    using const_fast_iterator = const_nditerator<numpy_expr>;

    static constexpr size_t value =
        utils::max_element<std::remove_reference<Args>::type::value...>::value;
    using value_type = decltype(Op()(std::declval<
        typename std::remove_reference<Args>::type::value_type>()...));
    using dtype = decltype(Op()(
        std::declval<typename std::remove_reference<Args>::type::dtype>()...));

#ifdef CYTHON_ABI
    std::tuple<typename std::remove_reference<Args>::type...> args;
#else
    std::tuple<Args...> args;
#endif
    using shape_t = sutils::merged_shapes_t<
        value, typename std::remove_reference<Args>::type::shape_t...>;
    static_assert(value == std::tuple_size<shape_t>::value,
                  "consistent shape and size");

    shape_t _shape;

    numpy_expr() = default;
    numpy_expr(numpy_expr const &) = default;
    numpy_expr(numpy_expr &&) = default;

    numpy_expr(Args const &... args);

    template <size_t... I>
    const_iterator _begin(utils::index_sequence<I...>) const;
    const_iterator begin() const;

    template <size_t... I>
    const_iterator _end(utils::index_sequence<I...>) const;
    const_iterator end() const;

    const_fast_iterator begin(types::fast) const;
    const_fast_iterator end(types::fast) const;

    template <size_t... I>
    iterator _begin(utils::index_sequence<I...>);
    iterator begin();

    template <size_t... I>
    iterator _end(utils::index_sequence<I...>);
    iterator end();

    template <size_t... I>
    auto _fast(long i, utils::index_sequence<I...>) const
        -> decltype(Op()(std::get<I>(args).fast(i)...))
    {
      return Op()(std::get<I>(args).fast(i)...);
    }

    auto fast(long i) const
        -> decltype(this->_fast(i,
                                utils::make_index_sequence<sizeof...(Args)>{}));

    template <size_t... I>
    auto _map_fast(array<long, sizeof...(I)> const &indices,
                   utils::index_sequence<I...>) const
        -> decltype(Op()(std::get<I>(args).fast(std::get<I>(indices))...))
    {
      return Op()(std::get<I>(args).fast(std::get<I>(indices))...);
    }

    template <class... Indices>
    auto map_fast(Indices... indices) const -> decltype(
        this->_map_fast(array<long, sizeof...(Indices)>{{indices...}},
                        utils::make_index_sequence<sizeof...(Args)>{}));

  public:
    shape_t const &shape() const
    {
      return _shape;
    }
    template <size_t... I>
    bool _no_broadcast(utils::index_sequence<I...>) const;
    bool no_broadcast() const;

#ifdef USE_XSIMD
    using simd_iterator = numpy_expr_simd_iterator<
        numpy_expr, Op,
        pshape<step_type_t<typename std::remove_reference<Args>::type>...>,
        std::tuple<
            typename std::remove_reference<Args>::type::const_iterator...>,
        typename std::remove_reference<Args>::type::simd_iterator...>;
    using simd_iterator_nobroadcast = numpy_expr_simd_iterator_nobroadcast<
        numpy_expr, Op, typename std::remove_reference<
                            Args>::type::simd_iterator_nobroadcast...>;
    template <size_t... I>
    simd_iterator _vbegin(types::vectorize, utils::index_sequence<I...>) const;
    simd_iterator vbegin(types::vectorize) const;
    template <size_t... I>
    simd_iterator _vend(types::vectorize, utils::index_sequence<I...>) const;
    simd_iterator vend(types::vectorize) const;

    template <size_t... I>
    simd_iterator_nobroadcast _vbegin(types::vectorize_nobroadcast,
                                      utils::index_sequence<I...>) const;
    simd_iterator_nobroadcast vbegin(types::vectorize_nobroadcast) const;
    template <size_t... I>
    simd_iterator_nobroadcast _vend(types::vectorize_nobroadcast,
                                    utils::index_sequence<I...>) const;
    simd_iterator_nobroadcast vend(types::vectorize_nobroadcast) const;

#endif
    template <size_t... I, class... S>
    auto _get(utils::index_sequence<I...>, S const &... s) const
        -> decltype(Op{}(std::get<I>(args)(s...)...))
    {
      return Op{}(std::get<I>(args)(s...)...);
    }

    template <class S0, class... S>
    auto operator()(S0 const &s0, S const &... s) const ->
        typename std::enable_if<
            !std::is_scalar<S0>::value || sizeof...(S) != 0,
            decltype(this->_get(utils::make_index_sequence<sizeof...(Args)>{},
                                s0, s...))>::type;

    template <class F>
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_expr, ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

    template <class F>
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_expr, ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value &&
                                !is_pod_array<F>::value,
                            numpy_vexpr<numpy_expr, F>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value &&
                                !is_pod_array<F>::value,
                            numpy_vexpr<numpy_expr, F>>::type
    fast(F const &filter) const;

    // FIXME: this does ! take into account bounds && broadcasting
    auto operator[](long i) const -> decltype(this->fast(i));

    template <size_t... I, class S>
    auto _index(S s, utils::index_sequence<I...>) const
        -> decltype(Op{}(std::get<I>(args)[s]...))
    {
      return Op{}(std::get<I>(args)[s]...);
    }
    auto operator[](slice s) const -> decltype(
        (*this)._index(s, utils::make_index_sequence<sizeof...(Args)>{}))
    {
      return _index(s, utils::make_index_sequence<sizeof...(Args)>{});
    }
    template <class L, class U>
    auto operator[](contiguous_slice<L, U> s) const -> decltype(
        (*this)._index(s, utils::make_index_sequence<sizeof...(Args)>{}))
    {
      return _index(s, utils::make_index_sequence<sizeof...(Args)>{});
    }

    dtype operator[](array<long, value> const &indices) const
    {
      return _index(indices, utils::make_index_sequence<sizeof...(Args)>{});
    }

    explicit operator bool() const;

    long flat_size() const;

    long size() const;
  };
}

template <class Op, class... Args>
struct assignable<types::numpy_expr<Op, Args...>> {
  using type = types::ndarray<
      typename pythonic::types::numpy_expr<Op, Args...>::dtype,
      typename pythonic::types::numpy_expr<Op, Args...>::shape_t>;
};

template <class Op, class... Arg>
struct lazy<types::numpy_expr<Op, Arg...>> {
  using type = types::numpy_expr<Op, typename lazy<Arg>::type...>;
};
PYTHONIC_NS_END
/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"
template <class Op, class K, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, indexable<K>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class K, class... Args>
struct __combined<indexable<K>, pythonic::types::numpy_expr<Op, Args...>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class K, class V, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>,
                  indexable_container<K, V>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class K, class V, class... Args>
struct __combined<indexable_container<K, V>,
                  pythonic::types::numpy_expr<Op, Args...>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class K, class... Args>
struct __combined<container<K>, pythonic::types::numpy_expr<Op, Args...>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class K, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, container<K>> {
  using type = pythonic::types::numpy_expr<Op, Args...>;
};

template <class Op, class Op2, class... Args, class... Args2>
struct __combined<pythonic::types::numpy_expr<Op, Args...>,
                  pythonic::types::numpy_expr<Op2, Args2...>> {
  using type = pythonic::types::ndarray<
      typename pythonic::types::numpy_expr<Op, Args...>::dtype,
      pythonic::types::array<long,
                             pythonic::types::numpy_expr<Op, Args...>::value>>;
};
template <class E, class Op, class... Args>
struct __combined<pythonic::types::numpy_iexpr<E>,
                  pythonic::types::numpy_expr<Op, Args...>> {
  using type = pythonic::types::numpy_iexpr<E>;
};
template <class E, class Op, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>,
                  pythonic::types::numpy_iexpr<E>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class T, class pS, class Op, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>,
                  pythonic::types::ndarray<T, pS>> {
  using type = pythonic::types::ndarray<T, pS>;
};

template <class T, class Op, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>,
                  pythonic::types::numpy_texpr<T>> {
  using type = pythonic::types::ndarray<
      typename pythonic::types::numpy_expr<Op, Args...>::dtype,
      pythonic::types::array<long,
                             pythonic::types::numpy_expr<Op, Args...>::value>>;
};

template <class T, class Op, class... Args>
struct __combined<pythonic::types::numpy_texpr<T>,
                  pythonic::types::numpy_expr<Op, Args...>> {
  using type = pythonic::types::ndarray<
      typename pythonic::types::numpy_expr<Op, Args...>::dtype,
      pythonic::types::array<long,
                             pythonic::types::numpy_expr<Op, Args...>::value>>;
};

/*}*/
#endif
