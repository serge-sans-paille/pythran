#ifndef PYTHONIC_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_UTILS_BROADCAST_COPY_HPP

#include "pythonic/include/utils/broadcast_copy.hpp"

#include "pythonic/types/tuple.hpp"
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

    template <bool vector_form, size_t N>
    template <class E, class F>
    void _broadcast_copy<vector_form, N, 0>::operator()(E &&self,
                                                        F const &other)
    {
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());
      if (other_size > 0) // empty array sometimes happen when filtering
      {
#ifdef _OPENMP
        if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT) {
          auto siter = self.begin();
          auto oiter = other.begin();
#pragma omp parallel for
          for (long i = 0; i < other_size; ++i)
            *(siter + i) = *(oiter + i);
        } else
#endif
          std::copy(other.begin(), other.end(), self.begin());

        // eventually repeat the pattern
        size_t n = self_size / other_size;
#ifdef _OPENMP
        if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
        else
#endif
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
      }
    }

    // ``D'' is not ``0'' so we should broadcast
    template <bool vector_form, size_t N, size_t D>
    template <class E, class F>
    void _broadcast_copy<vector_form, N, D>::operator()(E &&self,
                                                        F const &other)
    {
      auto sfirst = self.begin();
      auto siter = sfirst;
      *sfirst = other;
#ifdef _OPENMP
      long n = self.shape()[0];
      if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
        for (long i = 1; i < n; ++i)
          *(siter + i) = *sfirst;
      else
#endif
        std::fill(self.begin() + 1, self.end(), *sfirst);
    }

#ifdef USE_BOOST_SIMD
    // specialize for SIMD only if available
    // otherwise use the std::copy fallback
    template <class E, class F>
    void _broadcast_copy<true, 1, 0>::operator()(E &&self, F const &other)
    {
      using T = typename F::dtype;
      using vT = typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());

      if (other_size > 0) // empty array sometimes happen when filtering
      {
        static const std::size_t vN = boost::simd::meta::cardinal_of<vT>::value;
        auto oiter = other.vbegin();
        const long bound = std::distance(other.vbegin(), other.vend());

#ifdef _OPENMP
        if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (long i = 0; i < bound; ++i) {
            self.store(*(oiter + i), i * vN);
          }
        else
#endif
          for (long i = 0; i < bound * vN; i += vN, ++oiter)
            self.store(*oiter, i);
        // tail
        {
          auto siter = self.begin();
          auto oiter = other.begin();
          for (long i = bound * vN; i < other_size; ++i)
            *(siter + i) = *(oiter + i);
        }

        size_t n = self_size / other_size;
#ifdef _OPENMP
        if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
        else
#endif
          for (size_t i = 1; i < n; ++i)
            std::copy_n(self.begin(), other_size,
                        self.begin() + i * other_size);
      }
    }

#endif

    template <class E, class F, size_t N, size_t D, bool vector_form>
    E &broadcast_copy(E &self, F const &other)
    {
      _broadcast_copy<vector_form, N, D>{}(self, other);
      return self;
    }

    /* update
     */

    // ``D'' is not ``0'' so we should broadcast
    template <class Op, bool vector_form, size_t N, size_t D>
    template <class E, class F>
    void _broadcast_update<Op, vector_form, N, D>::operator()(E &&self,
                                                              F const &other)
    {
      long n = self.shape()[0];
      auto siter = self.begin();
#ifdef _OPENMP
      if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
        for (long i = 0; i < n; ++i)
          Op{}(*(siter + i), other);
      else
#endif
        for (long i = 0; i < n; ++i)
          Op{}(*(siter + i), other);
    }

    template <class Op, bool vector_form, size_t N>
    template <class E, class F>
    void _broadcast_update<Op, vector_form, N, 0>::operator()(E &&self,
                                                              F const &other)
    {
      long other_size = std::distance(other.begin(), other.end());
      if (other_size > 0) // empty array sometimes happen when filtering
      {
        auto siter = self.begin();
        auto oiter = other.begin();
#ifdef _OPENMP
        if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (long i = 0; i < other_size; ++i)
            Op{}(*(siter + i), *(oiter + i));
        else
#endif
            if (other_size == 1) {
          auto value = *oiter;
          for (auto send = self.end(); siter != send; ++siter)
            Op{}(*siter, value);
        } else
          for (auto send = self.end(); siter != send; siter += other_size)
            std::transform(siter, siter + other_size, oiter, siter, Op{});
      }
    }

    template <class Op, bool vector_form, size_t N>
    template <class E, class F0, class F1>
    void _broadcast_update<Op, vector_form, N, 0>::
    operator()(E &&self, types::broadcast<F0, F1> const &other)
    {
      auto value = *other.begin();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }

    template <class Op, bool vector_form, size_t N>
    template <class E, class F>
    void _broadcast_update<Op, vector_form, N, 0>::
    operator()(E &&self, types::broadcasted<F> const &other)
    {
      auto value = *other.end();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }

#ifdef USE_BOOST_SIMD
    // specialize for SIMD only if available
    // otherwise use the std::copy fallback
    template <class Op>
    template <class E, class F>
    void _broadcast_update<Op, true, 1, 0>::operator()(E &&self, F const &other)
    {
      using T = typename F::dtype;
      using vT = typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());

      if (other_size > 0) // empty array sometimes happen when filtering
      {
        static const std::size_t vN = boost::simd::meta::cardinal_of<vT>::value;
        auto oiter = other.vbegin();
        const long bound = std::distance(other.vbegin(), other.vend());

#ifdef _OPENMP
        if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
          for (long i = 0; i < bound * vN; i += vN) {
            self.store(Op{}(self.load(i), *(oiter + i)), i);
          }
        else
#endif
          for (long i = 0; i < bound * vN; i += vN, ++oiter)
            self.store(Op{}(self.load(i), *oiter), i);
        // tail
        {
          auto siter = self.begin();
          auto oiter = other.begin();
          for (long i = bound * vN; i < other_size; ++i)
            *(siter + i) = Op{}(*(siter + i), *(oiter + i));
        }
      }
    }
    template <class Op>
    template <class E, class F0, class F1>
    void _broadcast_update<Op, true, 1, 0>::
    operator()(E &&self, types::broadcast<F0, F1> const &other)
    {
      auto value = *other.begin();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }

    template <class Op>
    template <class E, class F>
    void _broadcast_update<Op, true, 1, 0>::
    operator()(E &&self, types::broadcasted<F> const &other)
    {
      auto value = *other.end();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }

#endif

    template <class Op, class E, class F, size_t N, size_t D, bool vector_form>
    E &broadcast_update(E &self, F const &other)
    {
      _broadcast_update<Op, vector_form, N, D>{}(self, other);
      return self;
    }
  }
}

#endif
