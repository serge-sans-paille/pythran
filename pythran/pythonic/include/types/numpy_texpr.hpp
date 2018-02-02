#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_TEXPR_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Arg, class... S>
  struct numpy_gexpr;
  template <class Arg, class F>
  struct numpy_fexpr;

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
    using value_type = numpy_gexpr<Arg, contiguous_slice, long>;
    using dtype = typename E::dtype;

    Arg arg;
    array<long, 2> _shape;
    array<long, 2> const &shape() const
    {
      return _shape;
    }

    numpy_texpr_2();
    numpy_texpr_2(numpy_texpr_2 const &) = default;
    numpy_texpr_2(numpy_texpr_2 &&) = default;

    numpy_texpr_2(Arg const &arg);
    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    auto fast(long i) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              i));

    auto fast(long i)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
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

#ifdef USE_BOOST_SIMD
    using simd_iterator = const_simd_nditerator<numpy_texpr_2>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    /* element filtering */
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_texpr_2, F>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value,
                            ndarray<dtype, 2>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_texpr_2, F>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value,
                            ndarray<dtype, 2>>::type
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
    template <class... Tys>
    auto operator[](std::tuple<Tys...> const &indices) -> decltype(
        arg[array<long, 2>{{std::get<1>(indices), std::get<0>(indices)}}]);
    template <class... Tys>
    auto operator[](std::tuple<Tys...> const &indices) const -> decltype(
        arg[array<long, 2>{{std::get<1>(indices), std::get<0>(indices)}}]);

    auto operator[](contiguous_slice const &s0) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0));
    auto operator[](contiguous_slice const &s0)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0));
    auto operator[](slice const &s0) const
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0));
    auto operator[](slice const &s0)
        -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                               pythonic::__builtin__::None),
                              s0));

    template <class S, size_t... I>
    auto _reverse_index(S const &indices, utils::index_sequence<I...>) const
        -> decltype(this->arg(std::get<I>(indices)...));

    template <class S0, class... S>
    auto operator()(S0 const &s0, S const &... s) const
        -> decltype(this->_reverse_index(
            std::tuple<S0 const &, S const &...>{s0, s...},
            utils::make_reversed_index_sequence<1 + sizeof...(S)>()));

    long flat_size() const;
    intptr_t id() const;
    ndarray<dtype, value> copy() const
    {
      return *this;
    }
  };

  // only implemented for N = 2
  template <class T>
  struct numpy_texpr<ndarray<T, 2>> : numpy_texpr_2<ndarray<T, 2>> {
    numpy_texpr();
    numpy_texpr(numpy_texpr const &) = default;
    numpy_texpr(numpy_texpr &&) = default;

    numpy_texpr(ndarray<T, 2> const &arg);
  };

  template <class E, class... S>
  struct numpy_texpr<numpy_gexpr<E, S...>>
      : numpy_texpr_2<numpy_gexpr<E, S...>> {
    numpy_texpr();
    numpy_texpr(numpy_texpr const &) = default;
    numpy_texpr(numpy_texpr &&) = default;

    numpy_texpr(numpy_gexpr<E, S...> const &arg);
  };
}

template <class Arg>
struct assignable<types::numpy_texpr<Arg>> {
  using type = types::ndarray<typename Arg::dtype, Arg::value>;
};

template <class T>
struct returnable<types::numpy_texpr<types::ndarray<T, 2>>> {
  using type = types::numpy_texpr<types::ndarray<T, 2>>;
};

template <class Arg>
struct lazy<types::numpy_texpr<Arg>> {
  using type = types::numpy_texpr<typename lazy<Arg>::type>;
};
PYTHONIC_NS_END

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"
template <class E, class K>
struct __combined<pythonic::types::numpy_texpr<E>, K> {
  using type = pythonic::types::numpy_texpr<E>;
};

/*}*/
#endif
