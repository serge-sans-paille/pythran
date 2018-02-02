#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/types/nditerator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

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

  template <class Op, class... Iters>
  struct numpy_expr_iterator
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<decltype(std::declval<
                          Op>()(*std::declval<Iters>()...))>::type> {
    std::array<long, sizeof...(Iters)> steps_;
    std::tuple<Iters...> iters_;

    numpy_expr_iterator(std::array<long, sizeof...(Iters)> steps,
                        Iters... iters)
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

    template <size_t... I>
    void _incr(utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{
          (std::get<I>(iters_) += steps_[I], true)...};
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
          (std::get<I>(iters_) += steps_[I] * i, true)...};
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
      std::initializer_list<long> distances{
          (std::get<I>(iters_) - std::get<I>(other.iters_))...};
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
      return (steps_[I - 1] &&
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
      return (!steps_[I - 1] ||
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
      if (steps_[I - 1] &&
          (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_)))
        return _lt(other, utils::int_<I - 1>{});
      else
        return steps_[I - 1] &&
               (std::get<I - 1>(iters_) < std::get<I - 1>(other.iters_));
    }

    bool operator<(numpy_expr_iterator const &other) const
    {
      return _lt(other, utils::int_<sizeof...(Iters)>{});
    }
  };
#ifdef USE_BOOST_SIMD
  template <class E, class Op, class SIters, class... Iters>
  struct numpy_expr_simd_iterator
      : std::iterator<std::random_access_iterator_tag,
                      typename std::remove_reference<decltype(std::declval<
                          Op>()(*std::declval<Iters>()...))>::type> {
    std::array<long, sizeof...(Iters)> steps_;
    std::tuple<Iters...> iters_;
    SIters siters_;

    numpy_expr_simd_iterator(std::array<long, sizeof...(Iters)> steps,
                             SIters const &siters, Iters... iters)
        : steps_(steps), siters_(siters), iters_(iters...)
    {
    }

    numpy_expr_simd_iterator(numpy_expr_simd_iterator const &other)
        : steps_(other.steps_), siters_(other.siters_), iters_(other.iters_)
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
      return Op{}(((steps_[I])
                       ? (*std::get<I>(iters_))
                       : (boost::simd::splat<decltype(*std::get<I>(iters_))>(
                             *std::get<I>(siters_))))...);
    }

    auto operator*() const -> decltype(
        this->_dereference(utils::make_index_sequence<sizeof...(Iters)>{}))
    {
      return _dereference(utils::make_index_sequence<sizeof...(Iters)>{});
    }

    template <size_t... I>
    void _incr(utils::index_sequence<I...>)
    {
      std::initializer_list<bool> _{
          (std::get<I>(iters_) += steps_[I], true)...};
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
          (std::get<I>(iters_) += steps_[I] * i, true)...};
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
      return (steps_[I - 1] &&
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
      return (steps_[I - 1] &&
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
      if (steps_[I - 1] &&
          (std::get<I - 1>(iters_) == std::get<I - 1>(other.iters_)))
        return _lt(other, utils::int_<I - 1>{});
      else
        return steps_[I - 1] &&
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
        types::is_vector_op<Op>::value;
    static const bool is_strided =
        utils::any_of<std::remove_reference<Args>::type::is_strided...>::value;
    using const_iterator = numpy_expr_iterator<
        Op, typename std::remove_reference<Args>::type::const_iterator...>;
    using iterator = numpy_expr_iterator<
        Op, typename std::remove_reference<Args>::type::iterator...>;
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
    array<long, value> _shape;

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
        -> decltype(Op()(std::get<I>(args).fast(i)...));

    auto fast(long i) const
        -> decltype(this->_fast(i,
                                utils::make_index_sequence<sizeof...(Args)>{}));

    template <size_t... I>
    auto _map_fast(std::array<long, sizeof...(I)> const &indices,
                   utils::index_sequence<I...>) const
        -> decltype(Op()(std::get<I>(args).fast(std::get<I>(indices))...));

    template <class... Indices>
    auto map_fast(Indices... indices) const -> decltype(
        this->_map_fast(std::array<long, sizeof...(Indices)>{{indices...}},
                        utils::make_index_sequence<sizeof...(Args)>{}));

  public:
    array<long, value> const &shape() const
    {
      return _shape;
    }
    template <size_t... I>
    bool _no_broadcast(utils::index_sequence<I...>) const;
    bool no_broadcast() const;

#ifdef USE_BOOST_SIMD
    using simd_iterator = numpy_expr_simd_iterator<
        numpy_expr, Op, std::tuple<typename std::remove_reference<
                            Args>::type::const_iterator...>,
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
        -> decltype(Op{}(std::get<I>(args)(s...)...));

    template <class S0, class... S>
    auto operator()(S0 const &s0, S const &... s) const ->
        typename std::enable_if<
            !std::is_scalar<S0>::value,
            decltype(this->_get(utils::make_index_sequence<sizeof...(Args)>{},
                                s0, s...))>::type;

    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_expr, F>>::type
    fast(F const &filter) const;

    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_expr, F>>::type
    operator[](F const &filter) const;
    // FIXME: this does ! take into account bounds && broadcasting
    auto operator[](long i) const -> decltype(this->fast(i));

    long flat_size() const;

    long size() const;
  };
}

template <class Op, class... Args>
struct assignable<types::numpy_expr<Op, Args...>> {
  using type =
      types::ndarray<typename pythonic::types::numpy_expr<Op, Args...>::dtype,
                     pythonic::types::numpy_expr<Op, Args...>::value>;
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
      pythonic::types::numpy_expr<Op, Args...>::value>;
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

/*}*/
#endif
