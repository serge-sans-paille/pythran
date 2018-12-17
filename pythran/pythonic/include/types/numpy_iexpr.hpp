#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/utils/array_helper.hpp"

#include <numeric>

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Arg, class... S>
  struct numpy_gexpr;

  /* Expression template for numpy expressions - indexing
   */
  template <class T, size_t N>
  struct numpy_iexpr_helper;

  template <class Arg> // Arg often is a reference, e.g. for something as
  // simple as a[i]
  struct numpy_iexpr {
    // wrapper around another numpy expression to skip first dimension using a
    // given value.
    static constexpr size_t value = std::remove_reference<Arg>::type::value - 1;
    static const bool is_vectorizable =
        std::remove_reference<Arg>::type::is_vectorizable;
    using dtype = typename std::remove_reference<Arg>::type::dtype;
    using value_type = typename std::remove_reference<decltype(
        numpy_iexpr_helper<numpy_iexpr, value>::get(std::declval<numpy_iexpr>(),
                                                    0L))>::type;

    static constexpr bool is_strided =
        std::remove_reference<Arg>::type::is_strided;

    using iterator =
        typename std::conditional<is_strided || value != 1,
                                  nditerator<numpy_iexpr>, dtype *>::type;
    using const_iterator =
        typename std::conditional<is_strided || value != 1,
                                  const_nditerator<numpy_iexpr>,
                                  dtype const *>::type;

    dtype *buffer;
    using shape_t =
        sutils::pop_head_t<typename std::remove_reference<Arg>::type::shape_t>;
    shape_t _shape;

    numpy_iexpr();
    numpy_iexpr(numpy_iexpr const &) = default;
    numpy_iexpr(numpy_iexpr &&) = default;

    numpy_iexpr(dtype *buffer, array<long, value> const &shape)
        : buffer(buffer), _shape(shape)
    {
    }

    template <class Argp> // ! using the default one, to make it possible to
    // accept reference && non reference version of
    // Argp
    numpy_iexpr(numpy_iexpr<Argp> const &other);

    numpy_iexpr(Arg const &arg, long index);
    numpy_iexpr(Arg const &arg, long index, dtype *b);

    long size() const;

    template <class E>
    numpy_iexpr &operator=(E const &expr);
    numpy_iexpr &operator=(numpy_iexpr const &expr);

    template <class Op, class E>
    numpy_iexpr &update_(E const &expr);

    template <class E>
    numpy_iexpr &operator+=(E const &expr);
    numpy_iexpr &operator+=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator-=(E const &expr);
    numpy_iexpr &operator-=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator*=(E const &expr);
    numpy_iexpr &operator*=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator/=(E const &expr);
    numpy_iexpr &operator/=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator&=(E const &expr);
    numpy_iexpr &operator&=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator|=(E const &expr);
    numpy_iexpr &operator|=(numpy_iexpr const &expr);

    template <class E>
    numpy_iexpr &operator^=(E const &expr);
    numpy_iexpr &operator^=(numpy_iexpr const &expr);

    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    dtype const *fbegin() const;
    dtype const *fend() const;

    dtype *fbegin();
    dtype const *fend();

    /* There are three kind of indexing operator: fast(long), [long] &&
     *(long):
     * - fast does ! perform automatic bound wrapping
     * - [] performs automatic bound wrapping, hen forwards to fast
     * - () is an alias to [] && directly forwards to []
     *
     * For each indexing operator, we have three variant: &, const& && &&:
     * - & means the numpy_iexpr has been bound to a non-const value, as in
     *``b=a[i] ; print b[j]``
     *   in that case the return type if the dim of a is 2 is a reference, to
     *allow ``b[j] = 1``
     * - const & means the numpy_iexpr has been bound to a const value, as in
     *``np.copy(a[i])``
     *   in that case the return type if the dim of a is 2 is a value (||
     *const ref)
     * - && means the numpy_iexpr is a r-value, which happens a lot, as in
     *``a[i][j]``
     *   in that case the return type if the dim of a is 2 is a reference.
     *   It is a bit weird because we return a refrence from a rvalue, but the
     *reference is bound to
     *   the buffer of ``a`` that is ! temp.
     */
    auto fast(long i) const
        & -> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
    }

    auto fast(long i) &
        -> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
    }

    auto fast(long i) &&
        -> decltype(
            numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i))
    {
      return numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i);
    }

    dtype const &fast(array<long, value> const &indices) const;
    dtype &fast(array<long, value> const &indices);

    template <size_t M>
    auto fast(array<long, M> const &indices) const
        -> decltype(nget<M - 1>()(*this, indices))
    {
      return nget<M - 1>()(*this, indices);
    }

    template <class F>
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value,
        numpy_vexpr<numpy_iexpr, ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

#ifdef USE_XSIMD
    using simd_iterator = const_simd_nditerator<numpy_iexpr>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif
    template <class... S>
    numpy_gexpr<numpy_iexpr, normalized_slice, normalize_t<S>...>
    operator()(slice const &s0, S const &... s) const;

    template <class... S>
    numpy_gexpr<numpy_iexpr, contiguous_normalized_slice, normalize_t<S>...>
    operator()(contiguous_slice const &s0, S const &... s) const;

    template <class... S>
    auto operator()(long s0, S const &... s) const
        -> decltype(std::declval<numpy_iexpr<numpy_iexpr>>()(s...))
    {
      return (*this)[s0](s...);
    }

    template <class F>
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value,
        numpy_vexpr<numpy_iexpr, ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;
    auto operator[](long i) const & -> decltype(this->fast(i));
    auto operator[](long i) & -> decltype(this->fast(i));
    auto operator[](long i) && -> decltype(std::move(*this).fast(i));
    numpy_gexpr<numpy_iexpr, normalized_slice>
    operator[](slice const &s0) const;
    numpy_gexpr<numpy_iexpr, contiguous_normalized_slice>
    operator[](contiguous_slice const &s0) const;

    dtype const &operator[](array<long, value> const &indices) const;
    dtype &operator[](array<long, value> const &indices);
    template <size_t M>
    auto operator[](array<long, M> const &indices) const
        & -> decltype(nget<M - 1>()(*this, indices))
    {
      return nget<M - 1>()(*this, indices);
    }

    explicit operator bool() const;
    long flat_size() const;
    shape_t const &shape() const
    {
      return _shape;
    }

    template <class pS>
    auto reshape(pS const &new_shape) const
        -> numpy_iexpr<decltype(std::declval<Arg>().reshape(
            std::declval<sutils::push_front_t<pS, long>>()))>
    {
      return {buffer, new_shape};
    }

    ndarray<dtype, shape_t> copy() const
    {
      return {*this};
    }

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value &&
                                !is_pod_array<F>::value,
                            numpy_vexpr<numpy_iexpr, F>>::type
    operator[](F const &filter) const
    {
      return {*this, filter};
    }

    template <class Ty>
    auto operator[](std::tuple<Ty> const &index) const
        -> decltype((*this)[std::get<0>(index)])
    {
      return (*this)[std::get<0>(index)];
    }

  private:
    /* compute the buffer offset, returning the offset between the
     * first element of the iexpr && the start of the buffer.
     * This used to be a plain loop, but g++ fails to unroll it, while it
     * unrolls it with the template version...
     */
    long buffer_offset(Arg const &shape, long index, utils::int_<0>);

    template <class T, class pS, size_t N>
    long buffer_offset(ndarray<T, pS> const &arg, long index, utils::int_<N>);

    template <class E, size_t N>
    long buffer_offset(E const &arg, long index, utils::int_<N>);
  };

  // Indexing an numpy_iexpr that has a dimension greater than one yields a
  // new numpy_iexpr
  template <class T, size_t N>
  struct numpy_iexpr_helper {
    static numpy_iexpr<T> get(T const &e, long i);
  };

  // Indexing an iexpr that has a dimension of one yields a qualified scalar.
  // The qualifier is either:
  // - a reference if the numpy_iexpr is a ref itself, as in ``b = a[i] ; b[i]
  // = 1``
  // - a reference if the numpy_iexpr is a r-value, as in ``a[i][j] = 1``
  // - a value if the numpy_iexpr is a const ref, as in ``b = a[i] ; c =
  // b[i]``
  template <class T>
  struct numpy_iexpr_helper<T, 1> {
    static typename T::dtype get(T const &e, long i);
    static typename T::dtype &get(T &&e, long i);
    static typename T::dtype &get(T &e, long i);
  };
}

template <class Arg>
struct assignable<types::numpy_iexpr<Arg>> {
  using type = types::numpy_iexpr<typename assignable<Arg>::type>;
};

template <class T, class pS>
struct assignable<types::numpy_iexpr<types::ndarray<T, pS> &>> {
  using type = types::numpy_iexpr<types::ndarray<T, pS> &>;
};

template <class T, class pS>
struct assignable<types::numpy_iexpr<types::ndarray<T, pS> const &>> {
  using type = types::numpy_iexpr<types::ndarray<T, pS> const &>;
};

template <class Arg>
struct returnable<types::numpy_iexpr<Arg>> {
  using type = types::numpy_iexpr<typename returnable<Arg>::type>;
};

template <class Arg>
struct lazy<types::numpy_iexpr<Arg>> {
  using type = types::numpy_iexpr<typename lazy<Arg>::type>;
};

template <class Arg>
struct lazy<types::numpy_iexpr<Arg const &>> {
  using type = types::numpy_iexpr<typename lazy<Arg>::type const &>;
};
PYTHONIC_NS_END

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"
template <class E, class K>
struct __combined<pythonic::types::numpy_iexpr<E>, indexable<K>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class E, class K>
struct __combined<indexable<K>, pythonic::types::numpy_iexpr<E>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class E, class K, class V>
struct __combined<pythonic::types::numpy_iexpr<E>, indexable_container<K, V>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class E, class K, class V>
struct __combined<indexable_container<K, V>, pythonic::types::numpy_iexpr<E>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class E, class K>
struct __combined<container<K>, pythonic::types::numpy_iexpr<E>> {
  using type = pythonic::types::numpy_iexpr<E>;
};

template <class E, class K>
struct __combined<pythonic::types::numpy_iexpr<E>, container<K>> {
  using type = pythonic::types::numpy_iexpr<E>;
};
template <class E0, class E1>
struct __combined<pythonic::types::numpy_iexpr<E0>,
                  pythonic::types::numpy_iexpr<E1>> {
  using type = pythonic::types::numpy_iexpr<typename __combined<E0, E1>::type>;
};
/*}*/
#endif
