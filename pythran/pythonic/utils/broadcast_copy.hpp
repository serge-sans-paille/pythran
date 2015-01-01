#ifndef PYTHONIC_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_UTILS_BROADCAST_COPY_HPP

#include "pythonic/types/tuple.hpp"
#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#endif

#ifdef _OPENMP
#include <omp.h>

// as a macro so that an enlightened user can modify this non-documented variable :-)
#ifndef PYTHRAN_OPENMP_MIN_ITERATION_COUNT
#define PYTHRAN_OPENMP_MIN_ITERATION_COUNT 1000
#endif

#endif

namespace pythonic {

  namespace utils {

        /* helper function to get the dimension of an array
         * yields 0 for scalar types
         */
        template <class T, typename EnableDefault = void>
        struct dim_of {
            static const size_t value = T::value;
        };

        template<class T, size_t N>
        struct dim_of<types::array<T,N>, void> {
            static const size_t value = 1 + dim_of<T>::value;
        };
        template<class T>
        struct dim_of<T, typename std::enable_if<std::is_fundamental<T>::value>::type> {
            static const size_t value = 0;
        };
#define SPECIALIZE_DIM_OF(TYPE) template<> struct dim_of<TYPE> { static const size_t value = 0; }
        SPECIALIZE_DIM_OF(std::complex<float>);
        SPECIALIZE_DIM_OF(std::complex<double>);
#undef SPECIALIZE_DIM_OF

        template<class T>
          struct _next {
            void operator()(T & iter) {
              iter.next();
            }
          };
        template<class T>
          struct _next<T const*> {
            void operator()(T const* & iter) {
              ++iter;
            }
          };
        template<class T>
          struct _next<T *> {
            void operator()(T * & iter) {
              ++iter;
            }
          };

        template<class T>
          void next(T& iter) {
            return _next<T>{}(iter);
          }

        template<class I, class O>
        void copy(I const& in, O& out) {
          if(in.is_broadcasting())
            std::copy(in.begin(), in.end(), out.begin());
          else {
            auto out_iter = out.begin();
            auto iter = in.begin(), iter_end = in.end();
            auto n = iter_end - iter;
            while(n--) {
              *out_iter = *iter;
              ::pythonic::utils::next(iter), ++out_iter;
            }
          }
        }

      /* helper for specialization of the broadcasting, vectorizing copy operator
       * due to expression templates, this may also triggers a lot of computations!
       *
       * ``vector_form'' is set to true if the operation can be done using Boost.SIMD
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
       * ``N'' is the depth of the loop nest. When it reaches ``1'', we have a raw loop
       *       that may be vectorizable
       *
       * ``D'' is the delta between the number of dimensions of E and F. When set to a
       *       value greater than ``0'', some broadcasting is needed
       */
      template <bool vector_form> struct _broadcast_copy {

        template <class E, class F, size_t N>
         void operator()(E &&self, F const &other, utils::int_<N>, utils::int_<0>) {
          long self_size = std::distance(self.begin(), self.end()),
               other_size = std::distance(other.begin(), other.end());
#ifdef _OPENMP
            if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for(long i = 0; i < other_size; ++i)
                self.fast(i) = other.fast(i);
            else
#endif
            copy(other, self);

            // eventually repeat the pattern
#ifdef _OPENMP
            if (other_size > 0 and self_size / other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for (size_t i = other_size; i < self_size; i+=other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i);
            else
#endif
              for (long i = other_size; i < self_size; i+= other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i);
        }

        // ``D'' is not ``0'' so we should broadcast
        template <class E, class F, size_t N, size_t D>
         void operator()(E &&self, F const &other, utils::int_<N>, utils::int_<D>) {
          self.fast(0) = other;
#ifdef _OPENMP
          long n = self.shape[0];
          if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
            #pragma omp parallel for
            for(long i = 1; i < n; ++i)
              self.fast(i) = self.fast(0);
          else
#endif
          std::fill(self.begin() + 1, self.end(), self.fast(0));
        }
      };

#ifdef USE_BOOST_SIMD
      // specialize for SIMD only if available
      // otherwise use the std::copy fallback
      template <> struct _broadcast_copy<true> {
        template <class E, class F>
         void operator()(E &&self, F const &other, utils::int_<1>, utils::int_<0>) {
          typedef typename F::dtype T;
          typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
          long self_size = std::distance(self.begin(), self.end()),
               other_size = std::distance(other.begin(), other.end());

            static const std::size_t vN = boost::simd::meta::cardinal_of<vT>::value;
            const long bound = other_size / vN * vN;

            long i;
#ifdef _OPENMP
            if (bound >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for (i = 0; i < bound; i += vN)
                self.store(other.load(i), i);
            else
#endif
              for (i = 0; i < bound; i += vN)
                self.store(other.load(i), i);
            for (; i < other_size; ++i)
              self.fast(i) = other.fast(i);

#ifdef _OPENMP
            if (other_size > 0 and self_size / other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for (size_t i = other_size; i < self_size; i+=other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i);
            else
#endif
              for (size_t i = other_size; i < self_size; i+= other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i );
          }
        }

        template <class E, class F, size_t N>
         void operator()(E &&self, F const &other, utils::int_<N>, utils::int_<0>) {
          long self_size = std::distance(self.begin(), self.end()),
               other_size = std::distance(other.begin(), other.end());
#ifdef _OPENMP
            if (other_size >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for(long i = 0; i < other_size; ++i)
                (*this)(self.fast(i), other.fast(i), utils::int_<N - 1>(), utils::int_<0>());
            else
#endif
              for(long i = 0; i < other_size; ++i)
                (*this)(self.fast(i), other.fast(i), utils::int_<N - 1>(), utils::int_<0>());

#ifdef _OPENMP
            size_t n = self_size / other_size;
            if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for (size_t i = other_size; i < self_size; i+=other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i);
            else
#endif
              for (size_t i = other_size; i < self_size; i+=other_size)
                std::copy_n(self.begin(), other_size, self.begin() + i);
          }
        }

        // ``D'' is not ``0'' so we should broadcast
        template <class E, class F, size_t N, size_t D>
         void operator()(E &&self, F const &other, utils::int_<N>, utils::int_<D>) {
          (*this)(self.fast(0), other, utils::int_<N - 1>(), utils::int_<D - 1>());
#ifdef _OPENMP
            long n = self.shape[0];
            if (n >= PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
              #pragma omp parallel for
              for(long i = 1; i < n; ++i)
                self.fast(i) = self.fast(0);
            else
#endif
              std::fill(self.begin() + 1, self.end(), self.fast(0));
        }

      };
#endif

      template <class E, class F, size_t N, size_t D, bool vector_form>
       E& broadcast_copy(E &self, F const &other) {
        _broadcast_copy<vector_form> {} (self, other, utils::int_<N>(), utils::int_<D>());
        return self;
      }
  }
}

#endif


