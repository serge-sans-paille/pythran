#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_TEXPR_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Arg, class... S>
  struct numpy_gexpr;

  /* expression template for Transposed matrix */
  template <class Arg>
  struct numpy_texpr;

  // wrapper around numpy expression for 2D transposed matrix using gexpr
  // representation
  // >>> b = a.transpose
  // >>> b[i] == a[:,i]
  // True
  //
  // for N = 2
  template <class E>
  struct numpy_texpr_2 {
    static_assert(E::value == 2, "texpr only implemented for matrices");
    static const bool is_vectorizable = false;
    static const bool is_strided = true;
    using Arg = E;

    using iterator = nditerator<numpy_texpr_2<Arg>>;
    using const_iterator = const_nditerator<numpy_texpr_2<Arg>>;

    static constexpr size_t value = Arg::value;
    using value_type = numpy_gexpr<
        Arg, typename contiguous_slice<none_type, none_type>::normalized_type,
        long>;
    using dtype = typename E::dtype;

    Arg arg;
    using shape_t = sutils::transpose_t<typename E::shape_t>;
    shape_t _shape;
    shape_t const &shape() const
    {
      return _shape;
    }

    numpy_texpr_2();
    numpy_texpr_2(numpy_texpr_2 const &) = default;
    numpy_texpr_2(numpy_texpr_2 &&) = default;
    numpy_texpr_2 &operator=(numpy_texpr_2 const &) = default;

    numpy_texpr_2(Arg const &arg);
    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    long size() const
    {
      return std::get<0>(_shape);
    }

    auto fast(long i) const -> decltype(this->arg(
        contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
        i));

    auto fast(long i) -> decltype(this->arg(
        contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
        i));
    auto fast(array<long, value> const &indices)
        -> decltype(arg.fast(array<long, 2>{{indices[1], indices[0]}}))
    {
      return arg.fast(array<long, 2>{{indices[1], indices[0]}});
    }
    auto fast(array<long, value> const &indices) const
        -> decltype(arg.fast(array<long, 2>{{indices[1], indices[0]}}))
    {
      return arg.fast(array<long, 2>{{indices[1], indices[0]}});
    }

#ifdef USE_XSIMD
    using simd_iterator = const_simd_nditerator<numpy_texpr_2>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    /* element filtering */
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value && F::value == 1 &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_texpr_2, ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value &&
                                F::value != 1 && !is_pod_array<F>::value,
                            numpy_vexpr<ndarray<dtype, pshape<long>>,
                                        ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            !std::is_same<bool, typename F::dtype>::value &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_texpr_2, ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value && F::value == 1 &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_texpr_2, ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value &&
                                F::value != 1 && !is_pod_array<F>::value,
                            numpy_vexpr<ndarray<dtype, pshape<long>>,
                                        ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            !std::is_same<bool, typename F::dtype>::value &&
            !is_pod_array<F>::value,
        numpy_vexpr<numpy_texpr_2, ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;
    auto operator[](long i) const -> decltype(this->fast(i));
    auto operator[](long i) -> decltype(this->fast(i));
    auto operator[](array<long, value> const &indices)
        -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}])
    {
      return arg[array<long, 2>{{indices[1], indices[0]}}];
    }
    auto operator[](array<long, value> const &indices) const
        -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}])
    {
      return arg[array<long, 2>{{indices[1], indices[0]}}];
    }
    template <class T0, class T1>
    auto operator[](std::tuple<T0, T1> const &indices) -> decltype(
        arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}])
    {
      return arg[std::tuple<T1, T0>{std::get<1>(indices),
                                    std::get<0>(indices)}];
    }

    template <class T0, class T1>
    auto operator[](std::tuple<T0, T1> const &indices) const -> decltype(
        arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}])
    {

      return arg[std::tuple<T1, T0>{std::get<1>(indices),
                                    std::get<0>(indices)}];
    }

    template <class L, class U>
    auto operator[](contiguous_slice<L, U> const &s0) const
        -> numpy_texpr<decltype(this->arg(
            contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                                   pythonic::__builtin__::None),
            s0))>;
    template <class L, class U>
    auto operator[](contiguous_slice<L, U> const &s0)
        -> numpy_texpr<decltype(this->arg(
            contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                                   pythonic::__builtin__::None),
            s0))>;
    auto operator[](slice const &s0) const -> numpy_texpr<decltype(this->arg(
        contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
        s0))>;
    auto operator[](slice const &s0) -> numpy_texpr<decltype(this->arg(
        contiguous_slice<none_type, none_type>(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
        s0))>;

    template <class S, size_t... I>
    auto _reverse_index(S const &indices, utils::index_sequence<I...>) const
        -> decltype(this->arg(std::get<I>(indices)...))
    {
      return arg(std::get<I>(indices)...);
    }
    ndarray<dtype, typename E::shape_t> copy() const
    {
      return *this;
    }

    template <class S0, class... S>
    auto
    operator()(S0 const &s0, S const &... s) const -> typename std::enable_if<
        !is_numexpr_arg<S0>::value,
        decltype(this->_reverse_index(
            std::tuple<S0 const &, S const &...>{s0, s...},
            utils::make_reversed_index_sequence<1 + sizeof...(S)>()))>::type;

    template <class S0, class... S>
    auto operator()(S0 const &s0, S const &... s) const ->
        typename std::enable_if<is_numexpr_arg<S0>::value,
                                decltype(this->copy()(s0, s...))>::type;

    explicit operator bool() const;
    long flat_size() const;
    intptr_t id() const;
    template <class Expr>
    numpy_texpr_2 &operator=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator=(numpy_texpr<Expr> const &expr);

    template <class Op, class Expr>
    numpy_texpr_2 &update_(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator+=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator-=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator*=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator/=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator&=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator|=(Expr const &expr);
    template <class Expr>
    numpy_texpr_2 &operator^=(Expr const &expr);

    template <class NewShape>
    ndarray<dtype, NewShape> reshape(NewShape const &shape) const
    {
      return copy().reshape(shape);
    }
  };

  // only implemented for N = 2
  template <class T, class S0, class S1>
  struct numpy_texpr<ndarray<T, pshape<S0, S1>>>
      : numpy_texpr_2<ndarray<T, pshape<S0, S1>>> {
    numpy_texpr() = default;
    numpy_texpr(numpy_texpr const &) = default;
    numpy_texpr(numpy_texpr &&) = default;
    numpy_texpr(ndarray<T, pshape<S0, S1>> const &arg);

    numpy_texpr &operator=(numpy_texpr const &) = default;

    using numpy_texpr_2<ndarray<T, pshape<S0, S1>>>::operator=;
  };
  template <class T>
  struct numpy_texpr<ndarray<T, array<long, 2>>>
      : numpy_texpr_2<ndarray<T, array<long, 2>>> {
    numpy_texpr() = default;
    numpy_texpr(numpy_texpr const &) = default;
    numpy_texpr(numpy_texpr &&) = default;
    numpy_texpr(ndarray<T, array<long, 2>> const &arg);

    numpy_texpr &operator=(numpy_texpr const &) = default;

    using numpy_texpr_2<ndarray<T, array<long, 2>>>::operator=;
  };

  template <class E, class... S>
  struct numpy_texpr<numpy_gexpr<E, S...>>
      : numpy_texpr_2<numpy_gexpr<E, S...>> {
    numpy_texpr() = default;
    numpy_texpr(numpy_texpr const &) = default;
    numpy_texpr(numpy_texpr &&) = default;
    numpy_texpr(numpy_gexpr<E, S...> const &arg);
    template <class F>
    numpy_texpr(numpy_texpr<F> const &other)
        : numpy_texpr(numpy_gexpr<E, S...>(other.arg))
    {
    }

    numpy_texpr &operator=(numpy_texpr const &) = default;

    using numpy_texpr_2<numpy_gexpr<E, S...>>::operator=;
  };
}

template <class Arg>
struct assignable<types::numpy_texpr<Arg>> {
  using type = types::numpy_texpr<typename assignable<Arg>::type>;
};

template <class Arg>
struct returnable<types::numpy_texpr<Arg>> {
  using type = types::numpy_texpr<typename returnable<Arg>::type>;
};

template <class Arg>
struct lazy<types::numpy_texpr<Arg>> {
  using type = types::numpy_texpr<typename lazy<Arg>::type>;
};
PYTHONIC_NS_END

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"
template <class E>
struct __combined<pythonic::types::numpy_texpr<E>,
                  pythonic::types::numpy_texpr<E>> {
  using type = pythonic::types::numpy_texpr<E>;
};
template <class E0, class E1>
struct __combined<pythonic::types::numpy_texpr<E0>,
                  pythonic::types::numpy_texpr<E1>> {
  using type = pythonic::types::numpy_texpr<typename __combined<E0, E1>::type>;
};

template <class E, class K>
struct __combined<pythonic::types::numpy_texpr<E>, K> {
  using type = pythonic::types::numpy_texpr<E>;
};

template <class E0, class E1, class... S>
struct __combined<pythonic::types::numpy_texpr<E0>,
                  pythonic::types::numpy_gexpr<E1, S...>> {
  using type = pythonic::types::numpy_texpr<E0>;
};

/*}*/
#endif
