#ifndef PYTHONIC_INCLUDE_TYPES_NDARRAY_HPP
#define PYTHONIC_INCLUDE_TYPES_NDARRAY_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/types/attr.hpp"

#include "pythonic/utils/nested_container.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/broadcast_copy.hpp"

#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/raw_array.hpp"

#include "pythonic/types/vectorizable_type.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/types/numpy_op_helper.hpp"
#include "pythonic/types/numpy_fexpr.hpp"
#include "pythonic/types/numpy_expr.hpp"
#include "pythonic/include/types/numpy_texpr.hpp"
#include "pythonic/types/numpy_iexpr.hpp"
#include "pythonic/types/numpy_gexpr.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include "pythonic/__builtin__/len.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#ifdef ENABLE_PYTHON_MODULE
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

#include <boost/python/object.hpp>
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
      ndarray(T *data, S const *pshape, PyObject *obj_ptr);
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
          ndarray<T, 1>>::type
      operator[](F const &filter) const;

      template <class F> // indexing through an array of indices -- a view
      typename std::enable_if<
          is_numexpr_arg<F>::value and
              not std::is_same<bool, typename F::dtype>::value,
          ndarray<T, 1>>::type
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
    using type = typename pythonic::types::numpy_expr_to_ndarray<
        pythonic::types::numpy_expr<Op, Args...>>::type::value_type;
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
        array<long, numpy_expr_to_ndarray<E>::N> operator()(E const &a);
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
        typename numpy_expr_to_ndarray<E>::T operator()(E const &a);
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

        typename numpy_expr_to_ndarray<E>::type make_imag(E const &a,
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
#include "pythonic/types/combined.hpp"

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
#include "pythonic/python/register_once.hpp"

namespace pythonic
{

  namespace details
  {
    constexpr int signed_int_types[] = {0, NPY_INT8, NPY_INT16, 0, NPY_INT32, 0,
                                        0, 0,        NPY_INT64};
    constexpr int unsigned_int_types[] = {
        0, NPY_UINT8, NPY_UINT16, 0, NPY_UINT32, 0, 0, 0, NPY_UINT64};
  }

  template <class T>
  struct c_type_to_numpy_type
      : c_type_to_numpy_type<decltype(std::declval<T>()())> {
  };

  template <>
  struct c_type_to_numpy_type<double>
      : std::integral_constant<int, NPY_DOUBLE> {
  };

  template <>
  struct c_type_to_numpy_type<float> : std::integral_constant<int, NPY_FLOAT> {
  };

  template <>
  struct c_type_to_numpy_type<std::complex<float>>
      : std::integral_constant<int, NPY_CFLOAT> {
  };

  template <>
  struct c_type_to_numpy_type<std::complex<double>>
      : std::integral_constant<int, NPY_CDOUBLE> {
  };

  template <>
  struct c_type_to_numpy_type<signed long long> {
    static const int value =
        details::signed_int_types[sizeof(signed long long)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned long long> {
    static const int value =
        details::unsigned_int_types[sizeof(unsigned long long)];
  };

  template <>
  struct c_type_to_numpy_type<signed long> {
    static const int value = details::signed_int_types[sizeof(signed long)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned long> {
    static const int value = details::unsigned_int_types[sizeof(unsigned long)];
  };

  template <>
  struct c_type_to_numpy_type<signed int> {
    static const int value = details::signed_int_types[sizeof(signed int)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned int> {
    static const int value = details::unsigned_int_types[sizeof(unsigned int)];
  };

  template <>
  struct c_type_to_numpy_type<signed short> {
    static const int value = details::signed_int_types[sizeof(signed short)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned short> {
    static const int value =
        details::unsigned_int_types[sizeof(unsigned short)];
  };

  template <>
  struct c_type_to_numpy_type<signed char> {
    static const int value = details::signed_int_types[sizeof(signed char)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned char> {
    static const int value = details::unsigned_int_types[sizeof(unsigned char)];
  };

  template <>
  struct c_type_to_numpy_type<bool> {
    static const int value = NPY_BOOL;
  };

  template <class T>
  struct c_type_to_numpy_type<boost::simd::logical<T>> {
    static const int value = NPY_BOOL;
  };

  template <typename T, size_t N>
  struct basic_array_checks {
    static PyArrayObject *check_array_type_and_dims(PyObject *obj_ptr);
  };

  template <typename T, size_t N>
  struct python_to_pythran<types::ndarray<T, N>> : basic_array_checks<T, N> {
    python_to_pythran();
    static void *convertible(PyObject *obj_ptr);
    static void
    construct(PyObject *obj_ptr,
              boost::python::converter::rvalue_from_python_stage1_data *data);
  };

  template <class T, class S>
  std::tuple<types::slice> make_slices(long const *strides, long const *offsets,
                                       S const *dims, utils::int_<1>);

  template <class T, class S, size_t N>
  auto make_slices(long const *strides, long const *offsets, S const *dims,
                   utils::int_<N>)
      -> decltype(std::tuple_cat(
          make_slices<T>(strides, offsets, dims, utils::int_<1>()),
          make_slices<T>(strides + 1, offsets + 1, dims + 1,
                         utils::int_<N - 1>())));

  template <typename T, size_t N, class... S>
  struct python_to_pythran<types::numpy_gexpr<types::ndarray<T, N>, S...>>
      : basic_array_checks<T, N> {
    python_to_pythran();
    static void *convertible(PyObject *obj_ptr);
    static void
    construct(PyObject *obj_ptr,
              boost::python::converter::rvalue_from_python_stage1_data *data);
  };

  template <typename E>
  struct python_to_pythran<types::numpy_texpr<E>>
      : basic_array_checks<typename E::dtype, E::value> {
    using T = typename E::dtype;
    static constexpr size_t N = E::value;

    python_to_pythran();
    static void *convertible(PyObject *obj_ptr);
    static void
    construct(PyObject *obj_ptr,
              boost::python::converter::rvalue_from_python_stage1_data *data);
  };

  template <typename T>
  struct custom_boost_simd_logical {
    static PyObject *convert(boost::simd::logical<T> const &n);
  };

  template <typename T>
  struct pythran_to_python<boost::simd::logical<T>> {
    pythran_to_python();
  };

  /* wrapper around Python array creation
   * its purpose is to hide the difference between the shape stored in pythran
   * (aka long) and the shape stored in numpy (aka npy_intp)
   * it should work (with an extra copy) on 32 bit architecture and without copy
   * on 64 bits architecture
   */
  template <class T, size_t N>
  struct pyarray_new {

    static_assert(!std::is_same<T, npy_intp>::value, "correctly specialized");

    PyObject *from_descr(PyTypeObject *subtype, PyArray_Descr *descr, T *dims,
                         void *data, int flags, PyObject *obj);
    PyObject *from_data(T *dims, int typenum, void *data);
  };

  template <size_t N>
  struct pyarray_new<npy_intp, N> {

    PyObject *from_descr(PyTypeObject *subtype, PyArray_Descr *descr,
                         npy_intp *dims, void *data, int flags, PyObject *obj);
    PyObject *from_data(npy_intp *dims, int typenum, void *data);
  };

  template <class T, size_t N>
  struct custom_array_to_ndarray {
    static PyObject *convert(types::ndarray<T, N> n);
  };

  template <class E>
  struct custom_expr_to_ndarray {
    static PyObject *convert(E n);
  };

  template <class T, size_t N>
  struct pythran_to_python<types::ndarray<T, N>> {
    pythran_to_python();
  };

  template <class Arg>
  struct pythran_to_python<types::numpy_iexpr<Arg>> {
    pythran_to_python();
  };

  template <class Arg, class... S>
  struct pythran_to_python<types::numpy_gexpr<Arg, S...>> {
    pythran_to_python();
  };
}

#endif

#endif
