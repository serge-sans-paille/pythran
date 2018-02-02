#ifndef PYTHONIC_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_UTILS_BROADCAST_COPY_HPP

#include "pythonic/include/utils/broadcast_copy.hpp"

#include "pythonic/types/tuple.hpp"

#ifdef _OPENMP
#include <omp.h>

// as a macro so that an enlightened user can modify this variable :-)
#ifndef PYTHRAN_OPENMP_MIN_ITERATION_COUNT
#define PYTHRAN_OPENMP_MIN_ITERATION_COUNT 1000
#endif

#endif

PYTHONIC_NS_BEGIN

namespace utils
{

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
   * ``D'' is the delta between the number of dimensions of E && F. When set
   *to a
   *       value greater than ``0'', some broadcasting is needed
   */

  template <typename vector_form, size_t N, size_t D>
  struct _broadcast_copy;

  template <size_t N, class vectorizer>
  struct _broadcast_copy<vectorizer, N, 0> {
    template <class E, class F>
    void operator()(E &&self, F const &other)
    {
      long self_size = std::distance(self.begin(), self.end()),
           other_size = std::distance(other.begin(), other.end());
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
#ifdef _OPENMP
      if (self_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT * other_size)
#pragma omp parallel for
        for (size_t i = other_size; i < self_size; i += other_size)
          std::copy_n(self.begin(), other_size, self.begin() + i);
      else
#endif
        for (size_t i = other_size; i < self_size; i += other_size)
          std::copy_n(self.begin(), other_size, self.begin() + i);
    }
  };

  // ``D'' is ! ``0'' so we should broadcast
  template <class vectorizer, size_t N, size_t D>
  struct _broadcast_copy {
    template <class E, class F>
    void operator()(E &&self, F const &other)
    {
      if (types::is_dtype<F>::value) {
        std::fill(self.begin(), self.end(), other);
      } else {
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
    }
  };

#ifdef USE_BOOST_SIMD
  // specialize for SIMD only if available
  // otherwise use the std::copy fallback
  template <class vectorizer, class E, class F>
  void vbroadcast_copy(E &&self, F const &other)
  {
    using T = typename F::dtype;
    using vT = typename boost::simd::pack<T>;
    long self_size = std::distance(self.begin(), self.end()),
         other_size = std::distance(other.begin(), other.end());
    static const std::size_t vN = vT::static_size;
    auto oiter = vectorizer::vbegin(other);
    const long bound =
        std::distance(vectorizer::vbegin(other), vectorizer::vend(other));

#ifdef _OPENMP
    if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT) {
      auto iter = vectorizer::vbegin(self);
#pragma omp parallel for
      for (long i = 0; i < bound; ++i) {
        (iter + i).store(*(oiter + i));
      }
    } else
#endif
      for (auto iter = vectorizer::vbegin(self), end = vectorizer::vend(self);
           iter != end; ++iter, ++oiter) {
        iter.store(*oiter);
      }
    // tail
    {
      auto siter = self.begin();
      auto oiter = other.begin();
      for (long i = bound * vN; i < other_size; ++i)
        *(siter + i) = *(oiter + i);
    }

#ifdef _OPENMP
    if (self_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT * other_size)
#pragma omp parallel for
      for (size_t i = other_size; i < self_size; i += other_size)
        std::copy_n(self.begin(), other_size, self.begin() + i);
    else
#endif
      for (size_t i = other_size; i < self_size; i += other_size)
        std::copy_n(self.begin(), other_size, self.begin() + i);
  }

  template <>
  struct _broadcast_copy<types::vectorizer, 1, 0> {
    template <class E, class F>
    void operator()(E &&self, F const &other)
    {
      return vbroadcast_copy<types::vectorizer>(std::forward<E>(self), other);
    }
  };
  template <>
  struct _broadcast_copy<types::vectorizer_nobroadcast, 1, 0> {
    template <class E, class F>
    void operator()(E &&self, F const &other)
    {
      return vbroadcast_copy<types::vectorizer_nobroadcast>(
          std::forward<E>(self), other);
    }
  };

#endif
  template <class E, class F, size_t N, size_t D, bool vector_form>
  struct broadcast_copy_dispatcher;

  template <class E, class F, size_t N, size_t D>
  struct broadcast_copy_dispatcher<E, F, N, D, false> {
    void operator()(E &self, F const &other)
    {
      if (utils::no_broadcast(other))
        _broadcast_copy<types::novectorize, N, D>{}(
            self, types::make_fast_range(other));
      else
        _broadcast_copy<types::novectorize, N, D>{}(self, other);
    }
  };
  template <class E, class F, size_t N, size_t D>
  struct broadcast_copy_dispatcher<E, F, N, D, true> {
    void operator()(E &self, F const &other)
    {
      if (utils::no_broadcast(other))
        _broadcast_copy<types::vectorizer_nobroadcast, N, D>{}(self, other);
      else
        _broadcast_copy<types::vectorizer, N, D>{}(self, other);
    }
  };

  template <class E, class F, size_t N, size_t D, bool vector_form>
  E &broadcast_copy(E &self, F const &other)
  {
    broadcast_copy_dispatcher<E, F, N, D, vector_form>{}(self, other);
    return self;
  }

  /* update
   */
  // ``D'' is ! ``0'' so we should broadcast
  template <class Op, typename vector_form, size_t N, size_t D>
  struct _broadcast_update {

    template <class E, class F>
    void operator()(E &&self, F const &other)
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
  };

  template <class Op, size_t N, class vector_form>
  struct _broadcast_update<Op, vector_form, N, 0> {
    template <class E, class F>
    void operator()(E &&self, F const &other)
    {
      long other_size = std::distance(other.begin(), other.end());
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
        for (auto send = self.end(); siter != send;) {
          auto ooiter = oiter;
          for (long i = 0; i < other_size; ++i, ++siter, ++ooiter)
            Op{}(*siter, *ooiter);
        }
    }

    template <class E, class F0, class F1>
    void operator()(E &&self, types::broadcast<F0, F1> const &other)
    {
      auto value = *other.begin();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }

    template <class E, class F>
    void operator()(E &&self, types::broadcasted<F> const &other)
    {
      auto value = *other.end();
      for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
        Op{}(*siter, value);
    }
  };

#ifdef USE_BOOST_SIMD
  // specialize for SIMD only if available
  // otherwise use the std::copy fallback
  template <class Op, class vectorizer, class E, class F>
  void vbroadcast_update(E &&self, F const &other)
  {
    using T = typename F::dtype;
    using vT = typename boost::simd::pack<T>;
    long self_size = std::distance(self.begin(), self.end()),
         other_size = std::distance(other.begin(), other.end());

    static const std::size_t vN = vT::static_size;
    auto oiter = vectorizer::vbegin(other);
    auto iter = vectorizer::vbegin(self);
    const long bound =
        std::distance(vectorizer::vbegin(other), vectorizer::vend(other));

#ifdef _OPENMP
    if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
#pragma omp parallel for
      for (long i = 0; i < bound; i++) {
        (iter + i).store(Op{}(*(iter + i), *(oiter + i)));
      }
    else
#endif
      for (auto end = vectorizer::vend(self); iter != end; ++iter, ++oiter) {
        iter.store(Op{}(*iter, *oiter));
      }
    // tail
    {
      auto siter = self.begin();
      auto oiter = other.begin();
      for (long i = bound * vN; i < other_size; ++i)
        Op{}(*(siter + i), *(oiter + i));
    }
  }

  template <class Op, class vectorizer, class E, class F0, class F1>
  void vbroadcast_update(E &&self, types::broadcast<F0, F1> const &other)
  {
    auto value = *other.begin();
    for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
      Op{}(*siter, value);
  }

  template <class Op, class vectorizer, class E, class F>
  void vbroadcast_update(E &&self, types::broadcasted<F> const &other)
  {
    auto value = *other.end();
    for (auto siter = self.begin(), send = self.end(); siter != send; ++siter)
      Op{}(*siter, value);
  }

  template <class Op>
  struct _broadcast_update<Op, types::vectorizer, 1, 0> {
    template <class... Args>
    void operator()(Args &&... args)
    {
      vbroadcast_update<Op, types::vectorizer>(std::forward<Args>(args)...);
    }
  };
  template <class Op>
  struct _broadcast_update<Op, types::vectorizer_nobroadcast, 1, 0> {
    template <class... Args>
    void operator()(Args &&... args)
    {
      vbroadcast_update<Op, types::vectorizer_nobroadcast>(
          std::forward<Args>(args)...);
    }
  };

#endif
  template <class Op, bool vector_form, class E, class F, size_t N, size_t D>
  struct broadcast_update_dispatcher;

  template <class Op, class E, class F, size_t N, size_t D>
  struct broadcast_update_dispatcher<Op, false, E, F, N, D> {
    void operator()(E &self, F const &other)
    {
      _broadcast_update<Op, types::novectorize, N, D>{}(self, other);
    }
  };
  template <class Op, class E, class F, size_t N, size_t D>
  struct broadcast_update_dispatcher<Op, true, E, F, N, D> {
    void operator()(E &self, F const &other)
    {
      if (utils::no_broadcast(other))
        _broadcast_update<Op, types::vectorizer_nobroadcast, N, D>{}(self,
                                                                     other);
      else
        _broadcast_update<Op, types::vectorizer, N, D>{}(self, other);
    }
  };

  template <class Op, class E, class F, size_t N, size_t D, bool vector_form>
  E &broadcast_update(E &self, F const &other)
  {
    broadcast_update_dispatcher<Op, vector_form, E, F, N, D>{}(self, other);
    return self;
  }
}
PYTHONIC_NS_END

#endif
