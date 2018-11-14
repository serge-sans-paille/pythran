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

#include "pythonic/include/numpy/bool_.hpp"
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
#include "pythonic/include/types/numpy_expr.hpp"
#include "pythonic/include/types/numpy_texpr.hpp"
#include "pythonic/include/types/numpy_iexpr.hpp"
#include "pythonic/include/types/numpy_gexpr.hpp"
#include "pythonic/include/types/numpy_vexpr.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include "pythonic/include/types/pointer.hpp"

#include "pythonic/include/__builtin__/len.hpp"

#include <cassert>
#include <ostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#ifdef ENABLE_PYTHON_MODULE
// Cython still uses the deprecated API, so we can't set this macro in this
// case!
#ifndef CYTHON_ABI
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif
#include "numpy/arrayobject.h"
#endif

#ifdef USE_XSIMD
#include <xsimd/xsimd.hpp>
#endif

PYTHONIC_NS_BEGIN

namespace types
{

  template <class T, class pS>
  struct ndarray;

  template <class T>
  struct type_helper;

  /* Helper for dimension-specific part of ndarray
   *
   * Instead of specializing the whole ndarray class, the dimension-specific
   *behavior are stored here.
   * There are two specialization for this type:
   * - a specialization depending on the dimensionality (==1 || > 1)
   * - a specialization depending on the constness.
   *
   * The raw ndarray<T,pS> specialization implies a *swallow copy* of the
   *ndarray, && thus a refcount increase.
   * It is meant to be used when indexing an rvalue, as in
   *``np.zeros(10)[i]``.
   *
   * The ndarray<T,pS> const& specialization implies a *reference copy*. It is
   *used when indexing a lvalue, as in ``a[i]``
   */

  template <class T, class pS>
  struct type_helper<ndarray<T, pS>> {
    static_assert(std::tuple_size<pS>::value != 1, "matching ok");
    using type = numpy_iexpr<ndarray<T, pS>>;
    using iterator = nditerator<ndarray<T, pS>>;
    using const_iterator = const_nditerator<ndarray<T, pS>>;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, pS> &n, long i);
    static const_iterator make_iterator(ndarray<T, pS> const &n, long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

    static numpy_iexpr<ndarray<T, pS>> get(ndarray<T, pS> &&self, long i);
    static long step(ndarray<T, pS> const &self);
  };

  template <class T, class pS>
  struct type_helper<ndarray<T, pS> const &> {
    static_assert(std::tuple_size<pS>::value != 1, "matching ok");
    using type = numpy_iexpr<ndarray<T, pS> const &>;

    using iterator = nditerator<ndarray<T, pS>>;
    using const_iterator = const_nditerator<ndarray<T, pS>>;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, pS> &n, long i);
    static const_iterator make_iterator(ndarray<T, pS> const &n, long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

    static numpy_iexpr<ndarray<T, pS> const &> get(ndarray<T, pS> const &self,
                                                   long i);
    static long step(ndarray<T, pS> const &self);
  };

  template <class T, class pS>
  struct type_helper<ndarray<T, pshape<pS>>> {
    using type = T;

    using iterator = T *;
    using const_iterator = T const *;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, pshape<pS>> &n, long i);
    static const_iterator make_iterator(ndarray<T, pshape<pS>> const &n,
                                        long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

    static type get(ndarray<T, pshape<pS>> &&self, long i);
    static constexpr long step(ndarray<T, pshape<pS>> const &);
  };

  template <class T, class pS>
  struct type_helper<ndarray<T, pshape<pS>> const &> {
    using type = T;

    using iterator = T *;
    using const_iterator = T const *;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, pshape<pS>> &n, long i);
    static const_iterator make_iterator(ndarray<T, pshape<pS>> const &n,
                                        long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);
    static type &get(ndarray<T, pshape<pS>> const &self, long i);
    static constexpr long step(ndarray<T, pshape<pS>> const &);
  };

  template <class T, class pS>
  struct type_helper<ndarray<T, array<pS, 1>>> {
    using type = T;

    using iterator = T *;
    using const_iterator = T const *;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, array<pS, 1>> &n, long i);
    static const_iterator make_iterator(ndarray<T, array<pS, 1>> const &n,
                                        long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);

    static type get(ndarray<T, array<pS, 1>> &&self, long i);
    static constexpr long step(ndarray<T, array<pS, 1>> const &);
  };

  template <class T, class pS>
  struct type_helper<ndarray<T, array<pS, 1>> const &> {
    using type = T;

    using iterator = T *;
    using const_iterator = T const *;

    type_helper() = delete; // Not intended to be instantiated

    static iterator make_iterator(ndarray<T, array<pS, 1>> &n, long i);
    static const_iterator make_iterator(ndarray<T, array<pS, 1>> const &n,
                                        long i);

    template <class S, class Iter>
    static T *initialize_from_iterable(S &shape, T *from, Iter &&iter);
    static type &get(ndarray<T, array<pS, 1>> const &self, long i);
    static constexpr long step(ndarray<T, array<pS, 1>> const &);
  };

  template <size_t L>
  struct noffset {
    template <size_t M>
    long operator()(array<long, M> const &strides,
                    array<long, M> const &indices) const;
    template <size_t M, class pS>
    long operator()(array<long, M> const &strides,
                    array<long, M> const &indices, pS const &shape) const;
  };

  template <>
  struct noffset<0> {
    template <size_t M>
    long operator()(array<long, M> const &,
                    array<long, M> const &indices) const;
    template <size_t M, class pS>
    long operator()(array<long, M> const &, array<long, M> const &indices,
                    pS const &shape) const;
  };

  /* Multidimensional array of values
   *
   * An ndarray wraps a raw array pointers && manages multiple dimensions
   * casted overt the raw data.
   * The number of dimensions is fixed as well as the type of the underlying
   * data.
   * A shared pointer is used internally to mimic Python's behavior.
   *
   */
  template <class T, class pS>
  struct ndarray {
    static const bool is_vectorizable = types::is_vectorizable<T>::value;
    static const bool is_strided = false;

    /* types */
    static constexpr size_t value = std::tuple_size<pS>::value;
    using dtype = T;
    using value_type = typename type_helper<ndarray>::type;
    using reference = value_type &;
    using const_reference = value_type const &;

    using iterator = typename type_helper<ndarray>::iterator;
    using const_iterator = typename type_helper<ndarray>::const_iterator;
    using flat_iterator = T *;
    using const_flat_iterator = T const *;

    using shape_t = pS;
    static_assert(std::tuple_size<shape_t>::value == value,
                  "consistent shape size");

    /* members */
    utils::shared_ref<raw_array<T>> mem; // shared data pointer
    T *buffer;      // pointer to the first data stored in the equivalent flat
                    // array
    shape_t _shape; // shape of the multidimensional array
    array<long, value> _strides; // strides

    /* mem management */
    void mark_memory_external(extern_type obj)
    {
      mem.external(obj);
      mem->forget();
    }

    /* constructors */
    ndarray();
    ndarray(ndarray const &) = default;
    ndarray(ndarray &&) = default;

    /* assignment */
    ndarray &operator=(ndarray const &other) = default;

    /* from other memory */
    ndarray(utils::shared_ref<raw_array<T>> const &mem, pS const &shape);
    ndarray(utils::shared_ref<raw_array<T>> &&mem, pS const &shape);

    /* from other array */
    template <class Tp, class pSp>
    ndarray(ndarray<Tp, pSp> const &other);

    /* from a seed */
    ndarray(pS const &shape, none_type init);
    ndarray(pS const &shape, T init);

    /* from a foreign pointer */
    template <class S>
    ndarray(T *data, S const *pshape, ownership o);
    ndarray(T *data, pS const &pshape, ownership o);

#ifdef ENABLE_PYTHON_MODULE
    template <class S>
    ndarray(T *data, S const *pshape, PyObject *obj);
    ndarray(T *data, pS const &pshape, PyObject *obj);
#endif

    template <
        class Iterable,
        class = typename std::enable_if<
            !is_array<typename std::remove_cv<
                typename std::remove_reference<Iterable>::type>::type>::value &&
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
    ndarray(numpy_vexpr<Arg, F> const &expr);

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

    template <class Expr>
    ndarray &operator^=(Expr const &expr);

    /* element indexing
     * differentiate const from non const, && r-value from l-value
     * */
    auto fast(long i) const
        & -> decltype(type_helper<ndarray const &>::get(*this, i))
    {
      return type_helper<ndarray const &>::get(*this, i);
    }

    auto fast(long i) &&
        -> decltype(type_helper<ndarray>::get(std::move(*this), i))
    {
      return type_helper<ndarray>::get(std::move(*this), i);
    }

    T &fast(array<long, value> const &indices);
    T fast(array<long, value> const &indices) const;

    template <size_t M>
    auto fast(array<long, M> const &indices) const
        & -> decltype(nget<M - 1>().fast(*this, indices));

    template <size_t M>
        auto fast(array<long, M> const &indices) &&
        -> decltype(nget<M - 1>().fast(std::move(*this), indices));

#ifdef USE_XSIMD
    using simd_iterator = const_simd_nditerator<ndarray>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    /* slice indexing */
    ndarray<T, sutils::push_front_t<pS, std::integral_constant<long, 1>>>
    operator[](none_type) const;

    numpy_gexpr<ndarray const &, normalized_slice>
    operator[](slice const &s) const &;
    numpy_gexpr<ndarray, normalized_slice> operator[](slice const &s) && ;

    numpy_gexpr<ndarray const &, contiguous_normalized_slice>
    operator[](contiguous_slice const &s) const;

    long size() const;

    /* extended slice indexing */
    template <class S0, class... S>
    auto operator()(S0 const &s0, S const &... s) const & -> decltype(
        extended_slice<count_new_axis<S0, S...>::value>{}((*this), s0, s...));

    template <class S0, class... S>
        auto operator()(S0 const &s0, S const &... s) &&
        -> decltype(extended_slice<count_new_axis<S0, S...>::value>{}(
            std::move(*this), s0, s...));

    /* element filtering */
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value && F::value == 1 &&
            !is_pod_array<F>::value,
        numpy_vexpr<ndarray, ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<
        is_numexpr_arg<F>::value &&
            std::is_same<bool, typename F::dtype>::value && F::value == 1 &&
            !is_pod_array<F>::value,
        numpy_vexpr<ndarray, ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value &&
                                F::value != 1 && !is_pod_array<F>::value,
                            numpy_vexpr<ndarray<T, pshape<long>>,
                                        ndarray<long, pshape<long>>>>::type
    fast(F const &filter) const;

    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value &&
                                F::value != 1 && !is_pod_array<F>::value,
                            numpy_vexpr<ndarray<T, pshape<long>>,
                                        ndarray<long, pshape<long>>>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value &&
                                !is_pod_array<F>::value,
                            numpy_vexpr<ndarray, F>>::type
    operator[](F const &filter) const;

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value &&
                                !is_pod_array<F>::value,
                            numpy_vexpr<ndarray, F>>::type
    fast(F const &filter) const;

    auto operator[](long i) const & -> decltype(this->fast(i))
    {
      if (i < 0)
        i += std::get<0>(_shape);
      return fast(i);
    }

    auto operator[](long i) && -> decltype(std::move(*this).fast(i))
    {
      if (i < 0)
        i += std::get<0>(_shape);
      return std::move(*this).fast(i);
    }

    T const &operator[](array<long, value> const &indices) const;

    T &operator[](array<long, value> const &indices);

    template <size_t M>
    auto operator[](array<long, M> const &indices) const
        & -> decltype(nget<M - 1>()(*this, indices));

    template <size_t M>
        auto operator[](array<long, M> const &indices) &&
        -> decltype(nget<M - 1>()(std::move(*this), indices));

    template <class Ty>
    auto operator[](std::tuple<Ty> const &indices) const
        -> decltype((*this)[std::get<0>(indices)])
    {
      return (*this)[std::get<0>(indices)];
    }

    template <class Ty0, class Ty1, class... Tys>
    auto operator[](std::tuple<Ty0, Ty1, Tys...> const &indices) const ->
        typename std::enable_if<
            !std::is_same<Ty0, long>::value && !is_numexpr_arg<Ty0>::value,
            decltype((*this)[to_array<long>(indices)])>::type;

    template <class Ty, class... Tys>
    auto operator[](std::tuple<long, Ty, Tys...> const &indices) const
        -> decltype((*this)[std::get<0>(indices)][tuple_tail(indices)])
    {
      return (*this)[std::get<0>(indices)][tuple_tail(indices)];
    }

    template <class L, class Ty, class... Tys>
    auto operator[](std::tuple<L, Ty, Tys...> const &indices) const ->
        typename std::enable_if<is_numexpr_arg<L>::value,
                                decltype((*this)[tuple_tail(indices)])>::type;

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

    template <class qS>
    ndarray<T, qS> reshape(qS const &shape) const &;
    template <class qS>
        ndarray<T, qS> reshape(qS const &shape) &&
        ;

    explicit operator bool() const;

    ndarray<T, pshape<long>> flat() const;
    ndarray<T, pS> copy() const;
    intptr_t id() const;
    pS const &shape() const;

    operator pointer<T>()
    {
      return {buffer};
    }
  };

  /* pretty printing { */
  template <class T, class pS>
  std::ostream &operator<<(std::ostream &os, ndarray<T, pS> const &e);

  template <class E>
  typename std::enable_if<is_array<E>::value, std::ostream &>::type
  operator<<(std::ostream &os, E const &e);
  /* } */
}
PYTHONIC_NS_END

/* std::get overloads */
namespace std
{

  template <size_t I, class E>
  auto get(E &&a) -> typename std::enable_if<
      pythonic::types::is_array<typename std::remove_cv<
          typename std::remove_reference<E>::type>::type>::value,
      decltype(std::forward<E>(a)[I])>::type;

  template <size_t I, class T, class pS>
  struct tuple_element<I, pythonic::types::ndarray<T, pS>> {
    using type = typename pythonic::types::ndarray<T, pS>::value_type;
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
PYTHONIC_NS_BEGIN

namespace types
{

  namespace details
  {
    template <class T>
    struct dtype_helper;

    template <>
    struct dtype_helper<bool> {
      using type = pythonic::numpy::functor::bool_;
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
#if defined(_WIN32) || defined(__APPLE__)
    template <>
    struct dtype_helper<long> : dtype_helper<int64_t> {
    };
#endif
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
      auto operator()(E const &a) -> decltype(sutils::array(a.shape()));
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
      auto operator()(E const &a) -> decltype(numpy::transpose(a))
      {
        return numpy::transpose(a);
      }
    };

    namespace
    {
      template <size_t N>
      struct _build_gexpr {
        template <class E, class... S>
        auto operator()(E const &a, S const &... slices)
            -> decltype(_build_gexpr<N - 1>{}(a, contiguous_slice(),
                                              slices...));
      };

      template <>
      struct _build_gexpr<1> {
        template <class E, class... S>
        numpy_gexpr<E, normalize_t<S>...> operator()(E const &a,
                                                     S const &... slices);
      };
    }

    template <class E>
    struct getattr<attr::REAL, E> {

      E make_real(E const &a, utils::int_<0>);

      auto make_real(E const &a, utils::int_<1>)
          -> decltype(_build_gexpr<E::value>{}(
              ndarray<typename types::is_complex<typename E::dtype>::type,
                      types::array<long, E::value>>{},
              slice()));

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
    struct getattr<attr::REAL, types::numpy_iexpr<E>> {

      auto operator()(types::numpy_iexpr<E> const &a) -> decltype(
          types::numpy_iexpr<decltype(getattr<attr::REAL, E>{}(a.arg))>{
              getattr<attr::REAL, E>{}(a.arg)})
      {
        return {getattr<attr::REAL, E>{}(a.arg)};
      }
    };

    template <class E, class... S>
    struct getattr<attr::REAL, types::numpy_gexpr<E, S...>> {

      template <class T, class Ss, size_t... Is>
      auto get(T &&expr, Ss const &indices, utils::index_sequence<Is...>)
          -> decltype(std::forward<T>(expr)(std::get<Is>(indices)...))
      {
        return std::forward<T>(expr)(std::get<Is>(indices)...);
      }
      auto operator()(types::numpy_gexpr<E, S...> const &a)
          -> decltype(this->get(
              getattr<attr::REAL, typename std::decay<E>::type>{}(a.arg),
              a.slices, utils::make_index_sequence<
                            std::tuple_size<decltype(a.slices)>::value>()))
      {
        return get(getattr<attr::REAL, typename std::decay<E>::type>{}(a.arg),
                   a.slices, utils::make_index_sequence<
                                 std::tuple_size<decltype(a.slices)>::value>());
      }
    };

    template <class E>
    struct getattr<attr::IMAG, E> {

      types::ndarray<typename E::dtype, typename E::shape_t>
      make_imag(E const &a, utils::int_<0>);

      auto make_imag(E const &a, utils::int_<1>)
          -> decltype(_build_gexpr<E::value>{}(
              ndarray<typename types::is_complex<typename E::dtype>::type,
                      types::array<long, E::value>>{},
              slice()));

      auto operator()(E const &a) -> decltype(this->make_imag(
          a, utils::int_<types::is_complex<typename E::dtype>::value>{}));
    };

    template <class E>
    struct getattr<attr::IMAG, types::numpy_texpr<E>> {
      auto operator()(types::numpy_texpr<E> const &a) -> decltype(
          types::numpy_texpr<decltype(getattr<attr::IMAG, E>{}(a.arg))>{
              getattr<attr::IMAG, E>{}(a.arg)});
    };

    template <class E>
    struct getattr<attr::IMAG, types::numpy_iexpr<E>> {

      auto operator()(types::numpy_iexpr<E> const &a) -> decltype(
          types::numpy_iexpr<decltype(getattr<attr::IMAG, E>{}(a.arg))>{
              getattr<attr::IMAG, E>{}(a.arg)})
      {
        return {getattr<attr::IMAG, E>{}(a.arg)};
      }
    };

    template <class E, class... S>
    struct getattr<attr::IMAG, types::numpy_gexpr<E, S...>> {

      template <class T, class Ss, size_t... Is>
      auto get(T &&expr, Ss const &indices, utils::index_sequence<Is...>)
          -> decltype(std::forward<T>(expr)(std::get<Is>(indices)...))
      {
        return std::forward<T>(expr)(std::get<Is>(indices)...);
      }
      auto operator()(types::numpy_gexpr<E, S...> const &a)
          -> decltype(this->get(
              getattr<attr::IMAG, typename std::decay<E>::type>{}(a.arg),
              a.slices, utils::make_index_sequence<
                            std::tuple_size<decltype(a.slices)>::value>()))
      {
        return get(getattr<attr::IMAG, typename std::decay<E>::type>{}(a.arg),
                   a.slices, utils::make_index_sequence<
                                 std::tuple_size<decltype(a.slices)>::value>());
      }
    };
  }
}
namespace __builtin__
{
  template <int I, class T, class pS>
  auto getattr(types::ndarray<T, pS> const &f)
      -> decltype(types::__ndarray::getattr<I, types::ndarray<T, pS>>()(f));

  template <int I, class O, class... Args>
  auto getattr(types::numpy_expr<O, Args...> const &f) -> decltype(
      types::__ndarray::getattr<I, types::numpy_expr<O, Args...>>()(f));

  template <int I, class A, class... S>
  auto getattr(types::numpy_gexpr<A, S...> const &f) -> decltype(
      types::__ndarray::getattr<I, types::numpy_gexpr<A, S...>>()(f));

  template <int I, class A>
  auto getattr(types::numpy_iexpr<A> const &f)
      -> decltype(types::__ndarray::getattr<I, types::numpy_iexpr<A>>()(f));

  template <int I, class A>
  auto getattr(types::numpy_texpr<A> const &f)
      -> decltype(types::__ndarray::getattr<I, types::numpy_texpr<A>>()(f));

  template <int I, class T, class F>
  auto getattr(types::numpy_vexpr<T, F> const &f)
      -> decltype(types::__ndarray::getattr<I, types::numpy_vexpr<T, F>>()(f));
}
PYTHONIC_NS_END

/* } */

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <class T1, class T2, class pS1, class pS2>
struct __combined<pythonic::types::ndarray<T1, pS1>,
                  pythonic::types::ndarray<T2, pS2>> {
  using type = pythonic::types::ndarray<typename __combined<T1, T2>::type, pS1>;
};

template <class pS, class T, class O>
struct __combined<pythonic::types::ndarray<T, pS>, O> {
  using type = pythonic::types::ndarray<T, pS>;
};

template <class pS, class T, class C, class I>
struct __combined<indexable_container<C, I>, pythonic::types::ndarray<T, pS>> {
  using type = pythonic::types::ndarray<T, pS>;
};

template <class pS, class T, class C>
struct __combined<indexable<C>, pythonic::types::ndarray<T, pS>> {
  using type = pythonic::types::ndarray<T, pS>;
};

template <class pS, class T, class C>
struct __combined<container<C>, pythonic::types::ndarray<T, pS>> {
  using type = pythonic::types::ndarray<T, pS>;
};

/* } */

#include "pythonic/include/types/numpy_operators.hpp"
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <class T, class pS>
struct to_python<types::ndarray<T, pS>> {
  static PyObject *convert(types::ndarray<T, pS> const &n,
                           bool transpose = false);
};

template <class Arg>
struct to_python<types::numpy_iexpr<Arg>> {
  static PyObject *convert(types::numpy_iexpr<Arg> const &v);
};

template <class Arg, class... S>
struct to_python<types::numpy_gexpr<Arg, S...>> {
  static PyObject *convert(types::numpy_gexpr<Arg, S...> const &v);
};

template <class T, class S0, class S1>
struct to_python<types::numpy_texpr<types::ndarray<T, types::pshape<S0, S1>>>> {
  static PyObject *
  convert(types::numpy_texpr<types::ndarray<T, types::pshape<S0, S1>>> const &t)
  {
    auto const &n = t.arg;
    PyObject *result =
        to_python<types::ndarray<T, types::pshape<S0, S1>>>::convert(n, true);
    return result;
  }
};

template <typename T, class pS>
struct from_python<types::ndarray<T, pS>> {
  static bool is_convertible(PyObject *obj);
  static types::ndarray<T, pS> convert(PyObject *obj);
};

template <typename T, class pS, class... S>
struct from_python<types::numpy_gexpr<types::ndarray<T, pS>, S...>> {
  static bool is_convertible(PyObject *obj);

  static types::numpy_gexpr<types::ndarray<T, pS>, S...> convert(PyObject *obj);
};
template <typename T, class pS, class... S>
struct from_python<types::numpy_gexpr<types::ndarray<T, pS> const &, S...>>
    : from_python<types::numpy_gexpr<types::ndarray<T, pS>, S...>> {
};

template <typename E>
struct from_python<types::numpy_texpr<E>> {

  static bool is_convertible(PyObject *obj);

  static types::numpy_texpr<E> convert(PyObject *obj);
};
PYTHONIC_NS_END

/* specialization of std::copy to avoid the multiple calls implied by the
 * recursive calls to std::copy */
namespace std
{
  template <class T, class pS>
  typename pythonic::types::nditerator<pythonic::types::ndarray<T, pS>> copy(
      typename pythonic::types::const_nditerator<
          pythonic::types::ndarray<T, pS>> begin,
      typename pythonic::types::const_nditerator<
          pythonic::types::ndarray<T, pS>> end,
      typename pythonic::types::nditerator<pythonic::types::ndarray<T, pS>> out)
  {
    const long offset = pythonic::sutils::prod_tail(begin.data.shape());
    std::copy(begin.data.buffer + begin.index * offset,
              end.data.buffer + end.index * offset,
              out.data.buffer + out.index * offset);
    return out + (end - begin);
  }
}

#endif

#endif
