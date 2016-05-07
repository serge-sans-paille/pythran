#ifndef PYTHONIC_INCLUDE_TYPES_NDARRAY_HPP
#define PYTHONIC_INCLUDE_TYPES_NDARRAY_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/empty_iterator.hpp"
#include "pythonic/include/types/attr.hpp"

#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/utils/shared_ref.hpp"
#include "pythonic/include/utils/reserve.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/broadcast_copy.hpp"

#include "pythonic/include/types/slice.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/raw_array.hpp"

#include "pythonic/include/numpy/uint8.hpp"
#include "pythonic/include/numpy/int8.hpp"
#include "pythonic/include/numpy/uint16.hpp"
#include "pythonic/include/numpy/int16.hpp"
#include "pythonic/include/numpy/uint32.hpp"
#include "pythonic/include/numpy/int32.hpp"
#include "pythonic/include/numpy/uint64.hpp"
#include "pythonic/include/numpy/int64.hpp"
#include "pythonic/include/numpy/float32.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/numpy/complex64.hpp"
#include "pythonic/include/numpy/complex128.hpp"

#include "pythonic/include/types/vectorizable_type.hpp"
#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/types/numpy_fexpr.hpp"
#include "pythonic/include/types/numpy_expr.hpp"
#include "pythonic/include/types/numpy_texpr.hpp"
#include "pythonic/include/types/numpy_iexpr.hpp"
#include "pythonic/include/types/numpy_gexpr.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include "pythonic/include/__builtin__/len.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#ifdef ENABLE_PYTHON_MODULE
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"
#endif

#include <boost/simd/sdk/simd/logical.hpp>

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

namespace pythonic
{

  namespace types
  {

    template <class T, size_t N>
    struct ndarray;

    template <class T>
    struct type_helper;

    /* Helper for dimension-specific part of ndarray
     *
     * Instead of specializing the whole ndarray class, the dimension-specific
     *behavior are stored here.
     * There are two specialization for this type:
     * - a specialization depending on the dimensionality (==1 or > 1)
     * - a specialization depending on the constness.
     *
     * The raw ndarray<T,N> specialization implies a *swallow copy* of the
     *ndarray, and thus a refcount increase.
     * It is meant to be used when indexing an rvalue, as in
     *``np.zeros(10)[i]``.
     *
     * The ndarray<T,N> const& specialization implies a *reference copy*. It is
     *used when indexing a lvalue, as in ``a[i]``
     */

    template <class T, size_t N>
    struct type_helper<ndarray<T, N>> {
      using type = numpy_iexpr<ndarray<T, N>>;
      using iterator = nditerator<ndarray<T, N>>;
      using const_iterator = const_nditerator<ndarray<T, N>>;

      type_helper() = delete; // Not intended to be instantiated

      static iterator make_iterator(ndarray<T, N> &n, long i);
      static const_iterator make_iterator(ndarray<T, N> const &n, long i);

      template <class S, class Iter>
      static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

      static numpy_iexpr<ndarray<T, N>> get(ndarray<T, N> &&self, long i);
      static long step(ndarray<T, N> const &self);
    };

    template <class T, size_t N>
    struct type_helper<ndarray<T, N> const &> {
      using type = numpy_iexpr<ndarray<T, N> const &>;

      using iterator = nditerator<ndarray<T, N>>;
      using const_iterator = const_nditerator<ndarray<T, N>>;

      type_helper() = delete; // Not intended to be instantiated

      static iterator make_iterator(ndarray<T, N> &n, long i);
      static const_iterator make_iterator(ndarray<T, N> const &n, long i);

      template <class S, class Iter>
      static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

      static numpy_iexpr<ndarray<T, N> const &> get(ndarray<T, N> const &self,
                                                    long i);
      static long step(ndarray<T, N> const &self);
    };

    template <class T>
    struct type_helper<ndarray<T, 1>> {
      using type = T;

      using iterator = T *;
      using const_iterator = T const *;

      type_helper() = delete; // Not intended to be instantiated

      static iterator make_iterator(ndarray<T, 1> &n, long i);
      static const_iterator make_iterator(ndarray<T, 1> const &n, long i);

      template <class S, class Iter>
      static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

      static type get(ndarray<T, 1> &&self, long i);
      static constexpr long step(ndarray<T, 1> const &);
    };

    template <class T>
    struct type_helper<ndarray<T, 1> const &> {
      using type = T;

      using iterator = T *;
      using const_iterator = T const *;

      type_helper() = delete; // Not intended to be instantiated

      static iterator make_iterator(ndarray<T, 1> &n, long i);
      static const_iterator make_iterator(ndarray<T, 1> const &n, long i);

      template <class S, class Iter>
      static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);
      static type &get(ndarray<T, 1> const &self, long i);
      static constexpr long step(ndarray<T, 1> const &);
    };

    /* recursively return the value at the position given by `indices' in
     * the `self' "array like". It may be a sub array instead of real value.
     * indices[0] is the coordinate for the first dimension and indices[M-1]
     * is for the last one.
     */
    template <size_t L>
    struct nget {
      template <class A, size_t M>
      auto operator()(A &&self, array<long, M> const &indices)
          -> decltype(nget<L - 1>()(std::forward<A>(self)[0], indices));
    };

    template <>
    struct nget<0> {
      template <class A, size_t M>
      auto operator()(A &&self, array<long, M> const &indices)
          -> decltype(std::forward<A>(self)[indices[M - 1]]);
    };

    template <size_t L>
    struct noffset {
      template <size_t M>
      long operator()(array<long, M> const &shape,
                      array<long, M> const &indices) const;
    };

    template <>
    struct noffset<0> {
      template <size_t M>
      long operator()(array<long, M> const &,
                      array<long, M> const &indices) const;
    };

    /* Multidimensional array of values
     *
     * An ndarray wraps a raw array pointers and manages multiple dimensions
     * casted overt the raw data.
     * The number of dimensions is fixed as well as the type of the underlying
     * data.
     * A shared pointer is used internally to mimic Python's behavior.
     *
     */
    template <class T, size_t N>
    struct ndarray {
      static const bool is_vectorizable = types::is_vectorizable<T>::value;
      static const bool is_strided = false;

      /* types */
      static constexpr size_t value = N;
      using dtype = T;
      using value_type = typename type_helper<ndarray>::type;
      using reference = value_type &;
      using const_reference = value_type const &;

      using iterator = typename type_helper<ndarray>::iterator;
      using const_iterator = typename type_helper<ndarray>::const_iterator;
      using flat_iterator = T *;
      using const_flat_iterator = T const *;

      /* members */
      utils::shared_ref<raw_array<T>> mem; // shared data pointer
      T *buffer; // pointer to the first data stored in the equivalent flat
                 // array
      array<long, N> _shape; // shape of the multidimensional array

      /* constructors */
      ndarray();
      ndarray(ndarray const &) = default;
      ndarray(ndarray &&) = default;

      /* assignment */
      ndarray &operator=(ndarray const &other) = default;

      /* from other memory */
      ndarray(utils::shared_ref<raw_array<T>> const &mem,
              array<long, N> const &shape);

      /* from other array */
      template <class Tp, size_t Np>
      ndarray(ndarray<Tp, Np> const &other);

      /* from a seed */
      ndarray(array<long, N> const &shape, none_type init);
      ndarray(array<long, N> const &shape, T init);

      /* from a foreign pointer */
      template <class S>
      ndarray(T *data, S const *pshape);

#ifdef ENABLE_PYTHON_MODULE
      template <class S>
      ndarray(T *data, S const *pshape, PyObject *obj);
#endif

      template <
          class Iterable,
          class = typename std::enable_if<
              !is_array<typename std::remove_cv<typename std::remove_reference<
                  Iterable>::type>::type>::value and
                  is_iterable<typename std::remove_cv<
                      typename std::remove_reference<Iterable>::type>::type>::
                      value,
              void>::type>
      ndarray(Iterable &&iterable);

      /* from a  numpy expression */
      template <class E>
      void initialize_from_expr(E const &expr);

      template <class Op, class... Args>
      ndarray(numpy_expr<Op, Args...> const &expr);

      template <class Arg>
      ndarray(numpy_texpr<Arg> const &expr);

      template <class Arg>
      ndarray(numpy_texpr_2<Arg> const &expr);

      template <class Arg, class... S>
      ndarray(numpy_gexpr<Arg, S...> const &expr);

      template <class Arg>
      ndarray(numpy_iexpr<Arg> const &expr);

      template <class Arg, class F>
      ndarray(numpy_fexpr<Arg, F> const &expr);

      /* update operators */
      template <class Op, class Expr>
      ndarray &update_(Expr const &expr);
      template <class Expr>
      ndarray &operator+=(Expr const &expr);

      template <class Expr>
      ndarray &operator-=(Expr const &expr);

      template <class Expr>
      ndarray &operator*=(Expr const &expr);

      template <class Expr>
      ndarray &operator/=(Expr const &expr);

      template <class Expr>
      ndarray &operator&=(Expr const &expr);

      template <class Expr>
      ndarray &operator|=(Expr const &expr);

      /* element indexing
       * differentiate const from non const, and r-value from l-value
       * */
      auto fast(long i) const
          & -> decltype(type_helper<ndarray const &>::get(*this, i));

      auto fast(long i) &&
          -> decltype(type_helper<ndarray>::get(std::move(*this), i));

      auto operator[](long i) const & -> decltype(this->fast(i));

      auto operator[](long i) && -> decltype(std::move(*this).fast(i));

      auto operator()(long i) const & -> decltype((*this)[i]);

      auto operator()(long i) && -> decltype(std::move (*this)[i]);

      T const &operator[](array<long, N> const &indices) const;

      T &operator[](array<long, N> const &indices);

      template <size_t M>
      auto operator[](array<long, M> const &indices) const
          & -> decltype(nget<M - 1>()(*this, indices));

      template <size_t M>
          auto operator[](array<long, M> const &indices) &&
          -> decltype(nget<M - 1>()(std::move(*this), indices));

#ifdef USE_BOOST_SIMD
      using simd_iterator = const_simd_nditerator<ndarray>;
      simd_iterator vbegin() const;
      simd_iterator vend() const;
      auto load(long i) const -> decltype(boost::simd::load<
          boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer, i));

      template <class V>
      void store(V &&v, long i);
#endif

      /* slice indexing */
      ndarray<T, N + 1> operator[](none_type) const;

      auto operator()(none_type const &n) const -> decltype((*this)[n]);

      numpy_gexpr<ndarray const &, slice> operator[](slice const &s) const;

      numpy_gexpr<ndarray const &, contiguous_slice>
      operator[](contiguous_slice const &s) const;

      numpy_gexpr<ndarray const &, slice> operator()(slice const &s) const;

      numpy_gexpr<ndarray const &, contiguous_slice>
      operator()(contiguous_slice const &s) const;

      long size() const;

      /* extended slice indexing */
      template <class S0, class... S>
      auto operator()(S0 const &s0, S const &... s) const -> decltype(
          extended_slice<count_new_axis<S0, S...>::value>{}((*this), s0, s...));

      template <class S0, class... S>
          auto operator()(S0 const &s0, S const &... s) &&
          -> decltype(extended_slice<count_new_axis<S0, S...>::value>{}(
              std::move(*this), s0, s...));

      /* element filtering */
      template <class F> // indexing through an array of boolean -- a mask
      typename std::enable_if<is_numexpr_arg<F>::value and
                                  std::is_same<bool, typename F::dtype>::value,
                              numpy_fexpr<ndarray, F>>::type
      fast(F const &filter) const;

      template <class F> // indexing through an array of boolean -- a mask
      typename std::enable_if<is_numexpr_arg<F>::value and
                                  std::is_same<bool, typename F::dtype>::value,
                              numpy_fexpr<ndarray, F>>::type
      operator[](F const &filter) const;

      template <class F> // indexing through an array of indices -- a view
      typename std::enable_if<
          is_numexpr_arg<F>::value and
              not std::is_same<bool, typename F::dtype>::value,
          ndarray<T, N>>::type
      operator[](F const &filter) const;

      template <class F> // indexing through an array of indices -- a view
      typename std::enable_if<
          is_numexpr_arg<F>::value and
              not std::is_same<bool, typename F::dtype>::value,
          ndarray<T, N>>::type
      fast(F const &filter) const;

      /* through iterators */
      iterator begin();
      const_iterator begin() const;
      iterator end();
      const_iterator end() const;

      const_flat_iterator fbegin() const;
      const_flat_iterator fend() const;
      flat_iterator fbegin();
      flat_iterator fend();

      /* member functions */
      long flat_size() const;
      bool may_overlap(ndarray const &) const;

      template <size_t M>
      ndarray<T, M> reshape(array<long, M> const &shape) const;

      ndarray<T, 1> flat() const;
      ndarray<T, N> copy() const;
      intptr_t id() const;
      array<long, N> const &shape() const;
    };

    /* pretty printing { */
    template <class T, size_t N>
    std::ostream &operator<<(std::ostream &os, ndarray<T, N> const &e);

    template <class E>
    typename std::enable_if<is_array<E>::value, std::ostream &>::type
    operator<<(std::ostream &os, E const &e);
    /* } */
  }
}

/* std::get overloads */
namespace std
{

  template <size_t I, class E>
  auto get(E &&a) -> typename std::enable_if<
      pythonic::types::is_array<typename std::remove_cv<
          typename std::remove_reference<E>::type>::type>::value,
      decltype(std::forward<E>(a)[I])>::type;

  template <size_t I, class T, size_t N>
  struct tuple_element<I, pythonic::types::ndarray<T, N>> {
    using type = typename pythonic::types::ndarray<T, N>::value_type;
  };

  template <size_t I, class Op, class... Args>
  struct tuple_element<I, pythonic::types::numpy_expr<Op, Args...>> {
    using type = typename pythonic::types::numpy_expr<Op, Args...>::dtype;
  };

  template <size_t I, class E>
  struct tuple_element<I, pythonic::types::numpy_iexpr<E>> {
    using type = decltype(std::declval<pythonic::types::numpy_iexpr<E>>()[0]);
  };

  template <size_t I, class E>
  struct tuple_element<I, pythonic::types::numpy_texpr<E>> {
    using type = decltype(std::declval<pythonic::types::numpy_texpr<E>>()[0]);
  };

  template <size_t I, class E, class... S>
  struct tuple_element<I, pythonic::types::numpy_gexpr<E, S...>> {
    using type =
        decltype(std::declval<pythonic::types::numpy_gexpr<E, S...>>()[0]);
  };
}

/* pythran attribute system { */
#include "pythonic/include/numpy/transpose.hpp"
namespace pythonic
{

  namespace types
  {

    namespace details
    {
      template <class T>
      struct dtype_helper;

      // FIXME: use another type?
      template <>
      struct dtype_helper<bool> {
        using type = pythonic::numpy::functor::uint8;
      };

      template <>
      struct dtype_helper<uint8_t> {
        using type = pythonic::numpy::functor::uint8;
      };
      template <>
      struct dtype_helper<int8_t> {
        using type = pythonic::numpy::functor::int8;
      };
      template <>
      struct dtype_helper<uint16_t> {
        using type = pythonic::numpy::functor::uint16;
      };
      template <>
      struct dtype_helper<int16_t> {
        using type = pythonic::numpy::functor::int16;
      };
      template <>
      struct dtype_helper<uint32_t> {
        using type = pythonic::numpy::functor::uint32;
      };
      template <>
      struct dtype_helper<int32_t> {
        using type = pythonic::numpy::functor::int32;
      };
      template <>
      struct dtype_helper<uint64_t> {
        using type = pythonic::numpy::functor::uint64;
      };
      template <>
      struct dtype_helper<int64_t> {
        using type = pythonic::numpy::functor::int64;
      };
      template <>
      struct dtype_helper<float> {
        using type = pythonic::numpy::functor::float32;
      };
      template <>
      struct dtype_helper<double> {
        using type = pythonic::numpy::functor::float64;
      };
      template <>
      struct dtype_helper<std::complex<float>> {
        using type = pythonic::numpy::functor::complex64;
      };
      template <>
      struct dtype_helper<std::complex<double>> {
        using type = pythonic::numpy::functor::complex128;
      };
    }
    template <class T>
    using dtype_t = typename details::dtype_helper<T>::type;

    namespace __ndarray
    {

      template <int I, class E>
      struct getattr;

      template <class E>
      struct getattr<attr::SHAPE, E> {
        auto operator()(E const &a) -> decltype(a.shape());
      };

      template <class E>
      struct getattr<attr::NDIM, E> {
        long operator()(E const &a);
      };

      template <class E>
      struct getattr<attr::STRIDES, E> {
        array<long, E::value> operator()(E const &a);
      };

      template <class E>
      struct getattr<attr::SIZE, E> {
        long operator()(E const &a);
      };

      template <class E>
      struct getattr<attr::ITEMSIZE, E> {
        long operator()(E const &a);
      };

      template <class E>
      struct getattr<attr::NBYTES, E> {
        long operator()(E const &a);
      };

      template <class E>
      struct getattr<attr::FLAT, E> {
        auto operator()(E const &a) -> decltype(a.flat());
      };

      template <class E>
      struct getattr<attr::DTYPE, E> {
        dtype_t<typename E::dtype> operator()(E const &);
      };

      template <class E>
      struct getattr<attr::T, E> {
        auto operator()(E const &a) -> decltype(numpy::transpose(a));
      };

      namespace
      {
        template <size_t N>
        struct _build_gexpr {
          template <class E, class... S>
          auto operator()(E const &a, S &&... slices)
              -> decltype(_build_gexpr<N - 1>{}(a, contiguous_slice(),
                                                std::forward<S>(slices)...));
        };

        template <>
        struct _build_gexpr<1> {
          template <class E, class... S>
          numpy_gexpr<E, S...> operator()(E const &a, S &&... slices);
        };
      }

      template <class E>
      struct getattr<attr::REAL, E> {

        E make_real(E const &a, utils::int_<0>);

        auto make_real(E const &a, utils::int_<1>)
            -> decltype(_build_gexpr<E::value>{}(
                ndarray<typename types::is_complex<typename E::dtype>::type,
                        E::value>{},
                slice{0, 0, 2}));

        auto operator()(E const &a) -> decltype(this->make_real(
            a, utils::int_<types::is_complex<typename E::dtype>::value>{}));
      };

      template <class E>
      struct getattr<attr::REAL, types::numpy_texpr<E>> {

        auto operator()(types::numpy_texpr<E> const &a) -> decltype(
            types::numpy_texpr<decltype(getattr<attr::REAL, E>{}(a.arg))>{
                getattr<attr::REAL, E>{}(a.arg)});
      };

      template <class E>
      struct getattr<attr::IMAG, E> {

        types::ndarray<typename E::dtype, E::value> make_imag(E const &a,
                                                              utils::int_<0>);

        auto make_imag(E const &a, utils::int_<1>)
            -> decltype(_build_gexpr<E::value>{}(
                ndarray<typename types::is_complex<typename E::dtype>::type,
                        E::value>{},
                slice{0, 0, 2}));

        auto operator()(E const &a) -> decltype(this->make_imag(
            a, utils::int_<types::is_complex<typename E::dtype>::value>{}));
      };

      template <class E>
      struct getattr<attr::IMAG, types::numpy_texpr<E>> {
        auto operator()(types::numpy_texpr<E> const &a) -> decltype(
            types::numpy_texpr<decltype(getattr<attr::IMAG, E>{}(a.arg))>{
                getattr<attr::IMAG, E>{}(a.arg)});
      };
    }
  }
  namespace __builtin__
  {
    template <int I, class T, size_t N>
    auto getattr(types::ndarray<T, N> const &f)
        -> decltype(types::__ndarray::getattr<I, types::ndarray<T, N>>()(f));

    template <int I, class O, class... Args>
    auto getattr(types::numpy_expr<O, Args...> const &f) -> decltype(
        types::__ndarray::getattr<I, types::numpy_expr<O, Args...>>()(f));

    template <int I, class A, class F>
    auto getattr(types::numpy_fexpr<A, F> const &f) -> decltype(
        types::__ndarray::getattr<I, types::numpy_fexpr<A, F>>()(f));

    template <int I, class A, class... S>
    auto getattr(types::numpy_gexpr<A, S...> const &f) -> decltype(
        types::__ndarray::getattr<I, types::numpy_gexpr<A, S...>>()(f));

    template <int I, class A>
    auto getattr(types::numpy_iexpr<A> const &f)
        -> decltype(types::__ndarray::getattr<I, types::numpy_iexpr<A>>()(f));

    template <int I, class A>
    auto getattr(types::numpy_texpr<A> const &f)
        -> decltype(types::__ndarray::getattr<I, types::numpy_texpr<A>>()(f));
  }
}

/* } */

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <class T1, class T2, size_t N, size_t M>
struct __combined<pythonic::types::ndarray<T1, N>,
                  pythonic::types::ndarray<T2, M>> {
  using type = pythonic::types::ndarray<typename __combined<T1, T2>::type, N>;
};

template <size_t N, class T, class O>
struct __combined<pythonic::types::ndarray<T, N>, O> {
  using type = pythonic::types::ndarray<T, N>;
};

template <size_t N, class T, class C, class I>
struct __combined<indexable_container<C, I>, pythonic::types::ndarray<T, N>> {
  using type = pythonic::types::ndarray<T, N>;
};

template <size_t N, class T, class C>
struct __combined<indexable<C>, pythonic::types::ndarray<T, N>> {
  using type = pythonic::types::ndarray<T, N>;
};

template <size_t N, class T, class C>
struct __combined<container<C>, pythonic::types::ndarray<T, N>> {
  using type = pythonic::types::ndarray<T, N>;
};

/* } */

#include "pythonic/include/types/numpy_operators.hpp"
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{

  template <class T, size_t N>
  struct to_python<types::ndarray<T, N>> {
    static PyObject *convert(types::ndarray<T, N> n);
  };

  template <class Arg>
  struct to_python<types::numpy_iexpr<Arg>> {
    static PyObject *convert(types::numpy_iexpr<Arg> const &v);
  };

  template <class Arg, class... S>
  struct to_python<types::numpy_gexpr<Arg, S...>> {
    static PyObject *convert(types::numpy_gexpr<Arg, S...> const &v);
  };

  template <typename T, size_t N>
  struct from_python<types::ndarray<T, N>> {
    static bool is_convertible(PyObject *obj);
    static types::ndarray<T, N> convert(PyObject *obj);
  };

  template <typename T, size_t N, class... S>
  struct from_python<types::numpy_gexpr<types::ndarray<T, N>, S...>> {
    static bool is_convertible(PyObject *obj);

    static types::numpy_gexpr<types::ndarray<T, N>, S...>
    convert(PyObject *obj);
  };

  template <typename E>
  struct from_python<types::numpy_texpr<E>> {

    static bool is_convertible(PyObject *obj);

    static types::numpy_texpr<E> convert(PyObject *obj);
  };
}

/* specialization of std::copy to avoid the multiple calls implied by the
 * recursive calls to std::copy */
namespace std
{
  template <class T, size_t N>
  typename pythonic::types::nditerator<pythonic::types::ndarray<T, N>> copy(
      typename pythonic::types::const_nditerator<pythonic::types::ndarray<T, N>>
          begin,
      typename pythonic::types::const_nditerator<pythonic::types::ndarray<T, N>>
          end,
      typename pythonic::types::nditerator<pythonic::types::ndarray<T, N>> out)
  {
    auto &&shape = begin.data.shape();
    const long offset = std::accumulate(shape.begin() + 1, shape.end(), 1L,
                                        std::multiplies<long>());
    std::copy(begin.data.buffer + begin.index * offset,
              end.data.buffer + end.index * offset,
              out.data.buffer + out.index * offset);
    return out + (end - begin);
  }
}

#endif

#endif
