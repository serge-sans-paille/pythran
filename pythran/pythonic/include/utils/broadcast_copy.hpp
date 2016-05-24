#ifndef PYTHONIC_INCLUDE_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_INCLUDE_UTILS_BROADCAST_COPY_HPP

#include "pythonic/include/types/tuple.hpp"
#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#endif

#ifdef _OPENMP
#include <omp.h>

// as a macro so that an enlightened user can modify this variable :-)
#ifndef PYTHRAN_OPENMP_MIN_ITERATION_COUNT
#define PYTHRAN_OPENMP_MIN_ITERATION_COUNT 1000
#endif

#endif

namespace pythonic
{

  namespace utils
  {

    /* helper function to get the dimension of an array
     * yields 0 for scalar types
     */
    template <class T, typename EnableDefault = void>
    struct dim_of {
      static const size_t value = T::value;
    };

    template <class T, size_t N>
    struct dim_of<types::array<T, N>, void> {
      static const size_t value = 1 + dim_of<T>::value;
    };

    template <class T>
    struct dim_of<
        T, typename std::enable_if<std::is_fundamental<T>::value>::type> {
      static const size_t value = 0;
    };

#define SPECIALIZE_DIM_OF(TYPE)                                                \
  template <>                                                                  \
  struct dim_of<TYPE> {                                                        \
    static const size_t value = 0;                                             \
  }

    SPECIALIZE_DIM_OF(std::complex<float>);
    SPECIALIZE_DIM_OF(std::complex<double>);

#undef SPECIALIZE_DIM_OF

    /* helper for specialization of the broadcasting, vectorizing copy operator
     * due to expression templates, this may also triggers a lot of
     *computations!
     *
     * ``vector_form'' is set to true if the operation can be done using
     *Boost.SIMD
     *
     * the call operator has four template parameters:
     *
     * template <class E, class F, size_t N>
     * void operator()(E &&self, F const &other, utils::int_<N>, utils::int_<M>)
     *
     * ``E'' is the type of the object to which the data are copied
     *
     * ``F'' is the type of the object from which the data are copied
     *
     * ``N'' is the depth of the loop nest. When it reaches ``1'', we have a raw
     *loop
     *       that may be vectorizable
     *
     * ``D'' is the delta between the number of dimensions of E and F. When set
     *to a
     *       value greater than ``0'', some broadcasting is needed
     */
    template <bool vector_form, size_t N, size_t D>
    struct _broadcast_copy {
      template <class E, class F>
      void operator()(E &&self, F const &other);
    };
    template <bool vector_form, size_t N>
    struct _broadcast_copy<vector_form, N, 0> {
      template <class E, class F>
      void operator()(E &&self, F const &other);
    };

#ifdef USE_BOOST_SIMD
    // specialize for SIMD only if available
    // otherwise use the std::copy fallback
    template <>
    struct _broadcast_copy<true, 1, 0> {
      template <class E, class F>
      void operator()(E &&self, F const &other);
    };
#endif

    template <class E, class F, size_t N, size_t D, bool vector_form>
    E &broadcast_copy(E &self, F const &other);

    // ``D'' is not ``0'' so we should broadcast
    template <class Op, bool vector_form, size_t N, size_t D>
    struct _broadcast_update {
      template <class E, class F>
      void operator()(E &&self, F const &other);
    };

    template <class Op, bool vector_form, size_t N>
    struct _broadcast_update<Op, vector_form, N, 0> {
      template <class E, class F>
      void operator()(E &&self, F const &other);

      template <class E, class F0, class F1>
      void operator()(E &&self, types::broadcast<F0, F1> const &other);
      template <class E, class F>
      void operator()(E &&self, types::broadcasted<F> const &other);
    };

#ifdef USE_BOOST_SIMD
    // specialize for SIMD only if available
    template <class Op>
    struct _broadcast_update<Op, true, 1, 0> {
      template <class E, class F>
      void operator()(E &&self, F const &other);
      template <class E, class F0, class F1>
      void operator()(E &&self, types::broadcast<F0, F1> const &other);
      template <class E, class F>
      void operator()(E &&self, types::broadcasted<F> const &other);
    };
#endif

    template <class Op, class E, class F, size_t N, size_t D, bool vector_form>
    E &broadcast_update(E &self, F const &other);
  }
}

#endif
