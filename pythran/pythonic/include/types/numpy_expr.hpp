#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_EXPR_HPP

#include "pythonic/include/utils/meta.hpp"

namespace pythonic
{

  namespace types
  {

    template <class Expr>
    struct is_numexpr_arg;

    template <class Expr, class... Slice>
    struct numpy_gexpr;

    /* Expression template for numpy expressions - binary operators
     */
    template <class Op, class... Args>
    struct numpy_expr {
      using first_arg = typename utils::front<Args...>::type;
      static const bool is_vectorizable =
          utils::all_of<
              std::remove_reference<Args>::type::is_vectorizable...>::value and
          utils::all_of<std::is_same<
              typename std::remove_cv<
                  typename std::remove_reference<first_arg>::type>::type::dtype,
              typename std::remove_cv<typename std::remove_reference<
                  Args>::type>::type::dtype>::value...>::value and
          types::is_vector_op<Op>::value;
      static const bool is_strided = utils::any_of<
          std::remove_reference<Args>::type::is_strided...>::value;
      using iterator = const_nditerator<numpy_expr>;
      static constexpr size_t value = utils::max_element<
          std::remove_reference<Args>::type::value...>::value;
      using value_type = decltype(Op()(std::declval<
          typename std::remove_reference<Args>::type::value_type>()...));
      using dtype = decltype(Op()(std::declval<
          typename std::remove_reference<Args>::type::dtype>()...));

      std::tuple<typename std::remove_reference<Args>::type...> args;
      array<long, value> _shape;

      numpy_expr();
      numpy_expr(numpy_expr const &) = default;
      numpy_expr(numpy_expr &&) = default;

      numpy_expr(Args const &... args);

      iterator begin() const;
      iterator end() const;

      template <int... I>
      auto _fast(long i, utils::seq<I...>) const
          -> decltype(Op()(std::get<I>(args).fast(i)...));

      auto fast(long i) const -> decltype(
          this->_fast(i, typename utils::gens<sizeof...(Args)>::type{}));

      auto operator[](long i) const -> decltype(this->fast(i));
      auto operator()(long i) const -> decltype(this->fast(i));

      array<long, value> const &shape() const;

#ifdef USE_BOOST_SIMD
      template <int... I>
      auto _load(long i, utils::seq<I...>) const
          -> decltype(Op()(std::get<I>(args).load(i)...));

      template <class I> // template to prevent automatic instantiation when the
      // type is not vectorizable
      auto load(I i) const -> decltype(
          this->_load(i, typename utils::gens<sizeof...(Args)>::type{}));
#endif
      template <int... I, class... S>
      auto _get(utils::seq<I...>, S const &... s) const
          -> decltype(Op{}(std::get<I>(args)(s...)...));

      template <class S0, class... S>
      auto operator()(S0 const &s0, S const &... s) const ->
          typename std::enable_if<
              not std::is_scalar<S0>::value,
              decltype(this->_get(typename utils::gens<sizeof...(Args)>::type{},
                                  s0, s...))>::type;

      template <class F>
      typename std::enable_if<is_numexpr_arg<F>::value,
                              numpy_fexpr<numpy_expr, F>>::type
      fast(F const &filter) const;

      template <class F>
      typename std::enable_if<is_numexpr_arg<F>::value,
                              numpy_fexpr<numpy_expr, F>>::type
      operator[](F const &filter) const;

      template <int... I>
      long _flat_size(utils::seq<I...>) const;

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
}
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

/*}*/
#endif
