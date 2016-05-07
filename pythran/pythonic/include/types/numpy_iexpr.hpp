#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/types/tuple.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <numeric>

namespace pythonic
{

  namespace types
  {

    template <class Arg, class... S>
    struct numpy_gexpr;
    template <class Arg, class F>
    struct numpy_fexpr;

    /* Expression template for numpy expressions - indexing
     */
    template <class T, size_t N>
    struct numpy_iexpr_helper;

    template <class Arg> // Arg often is a reference, e.g. for something as
    // simple as a[i]
    struct numpy_iexpr {
      // wrapper around another numpy expression to skip first dimension using a
      // given value.
      static constexpr size_t value =
          std::remove_reference<Arg>::type::value - 1;
      static const bool is_vectorizable =
          std::remove_reference<Arg>::type::is_vectorizable;
      using dtype = typename std::remove_reference<Arg>::type::dtype;
      using value_type = typename std::remove_reference<decltype(
          numpy_iexpr_helper<numpy_iexpr, value>::get(
              std::declval<numpy_iexpr>(), 0L))>::type;

      static constexpr bool is_strided =
          std::remove_reference<Arg>::type::is_strided;

      using iterator =
          typename std::conditional<is_strided or value != 1,
                                    nditerator<numpy_iexpr>, dtype *>::type;
      using const_iterator =
          typename std::conditional<is_strided or value != 1,
                                    const_nditerator<numpy_iexpr>,
                                    dtype const *>::type;

      Arg arg;
      dtype *buffer;
      array<long, value> _shape;

      numpy_iexpr();
      numpy_iexpr(numpy_iexpr const &) = default;
      numpy_iexpr(numpy_iexpr &&) = default;

      template <class Argp> // not using the default one, to make it possible to
      // accept reference and non reference version of
      // Argp
      numpy_iexpr(numpy_iexpr<Argp> const &other);

      numpy_iexpr(Arg const &arg, long index);
      // force the move. Using universal reference here does not work (because
      // of reference collapsing ?)
      numpy_iexpr(typename std::remove_reference<Arg>::type &&arg, long index);

      long size() const;

      template <class E>
      numpy_iexpr &operator=(E const &expr);
      numpy_iexpr &operator=(numpy_iexpr const &expr);

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

      const_iterator begin() const;
      const_iterator end() const;

      iterator begin();
      iterator end();

      dtype const *fbegin() const;
      dtype const *fend() const;

      dtype *fbegin();
      dtype const *fend();

      /* There are three kind of indexing operator: fast(long), [long] and
       *(long):
       * - fast does not perform automatic bound wrapping
       * - [] performs automatic bound wrapping, hen forwards to fast
       * - () is an alias to [] and directly forwards to []
       *
       * For each indexing operator, we have three variant: &, const& and &&:
       * - & means the numpy_iexpr has been bound to a non-const value, as in
       *``b=a[i] ; print b[j]``
       *   in that case the return type if the dim of a is 2 is a reference, to
       *allow ``b[j] = 1``
       * - const & means the numpy_iexpr has been bound to a const value, as in
       *``np.copy(a[i])``
       *   in that case the return type if the dim of a is 2 is a value (or
       *const ref)
       * - && means the numpy_iexpr is a r-value, which happens a lot, as in
       *``a[i][j]``
       *   in that case the return type if the dim of a is 2 is a reference.
       *   It is a bit weird because we return a refrence from a rvalue, but the
       *reference is bound to
       *   the buffer of ``a`` that is not temp.
       */
      auto fast(long i) const
          & -> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i));

      auto fast(long i) &
          -> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i));

      auto fast(long i) &&
          -> decltype(
              numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i));

#ifdef USE_BOOST_SIMD
      using simd_iterator = const_simd_nditerator<numpy_iexpr>;
      simd_iterator vbegin() const;
      simd_iterator vend() const;
      template <class I>
      auto load(I i) const -> decltype(boost::simd::load<
          boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(
          this->buffer, i));

      template <class V>
      void store(V &&v, long i);
#endif
      auto operator[](long i) const & -> decltype(this->fast(i));
      auto operator[](long i) & -> decltype(this->fast(i));
      auto operator[](long i) && -> decltype(std::move(*this).fast(i));
      auto operator()(long i) const & -> decltype((*this)[i]);
      auto operator()(long i) & -> decltype((*this)[i]);
      auto operator()(long i) && -> decltype(std::move (*this)[i]);
      numpy_gexpr<numpy_iexpr, slice> operator()(slice const &s0) const;
      numpy_gexpr<numpy_iexpr, slice> operator[](slice const &s0) const;

      numpy_gexpr<numpy_iexpr, contiguous_slice>
      operator()(contiguous_slice const &s0) const;

      numpy_gexpr<numpy_iexpr, contiguous_slice>
      operator[](contiguous_slice const &s0) const;

      template <class... S>
      numpy_gexpr<numpy_iexpr, slice, S...> operator()(slice const &s0,
                                                       S const &... s) const;

      template <class... S>
      numpy_gexpr<numpy_iexpr, contiguous_slice, S...>
      operator()(contiguous_slice const &s0, S const &... s) const;

      template <class... S>
      auto operator()(long s0, S const &... s) const
          -> decltype(std::declval<numpy_iexpr<numpy_iexpr>>()(s...));

      template <class F>
      typename std::enable_if<is_numexpr_arg<F>::value,
                              numpy_fexpr<numpy_iexpr, F>>::type
      fast(F const &filter) const;

      template <class F>
      typename std::enable_if<is_numexpr_arg<F>::value,
                              numpy_fexpr<numpy_iexpr, F>>::type
      operator[](F const &filter) const;

      dtype const &operator[](array<long, value> const &indices) const;
      dtype &operator[](array<long, value> const &indices);

      long flat_size() const;
      array<long, value> const &shape() const;

    private:
      /* compute the buffer offset, returning the offset between the
       * first element of the iexpr and the start of the buffer.
       * This used to be a plain loop, but g++ fails to unroll it, while it
       * unrolls it with the template version...
       */
      long buffer_offset(long index, utils::int_<0>);

      template <size_t N>
      long buffer_offset(long index, utils::int_<N>);
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

  template <class T, size_t N>
  struct assignable<types::numpy_iexpr<types::ndarray<T, N> &>> {
    using type = types::numpy_iexpr<types::ndarray<T, N> &>;
  };

  template <class T, size_t N>
  struct assignable<types::numpy_iexpr<types::ndarray<T, N> const &>> {
    using type = types::numpy_iexpr<types::ndarray<T, N> const &>;
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
}

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
