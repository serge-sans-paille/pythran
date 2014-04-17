#ifndef PYTHONIC_UTILS_BROADCAST_COPY_HPP
#define PYTHONIC_UTILS_BROADCAST_COPY_HPP

#include "pythonic/types/tuple.hpp"

#ifdef _OPENMP
#include <omp.h>
#ifndef PYTHRAN_OPENMP_MIN_ITERATION_COUNT
#define PYTHRAN_OPENMP_MIN_ITERATION_COUNT 1000
#endif
#endif

namespace pythonic {

    namespace utils {

        /* helper function to get the dimension of an array
         * yields 0 for scalar types
         */
        template <class T>
        struct dim_of {
            static const size_t value = T::value;
        };

#define SPECIALIZE_DIM_OF(TYPE) template<> struct dim_of<TYPE> { static const size_t value = 0; }
        SPECIALIZE_DIM_OF(bool);
        SPECIALIZE_DIM_OF(int8_t);
        SPECIALIZE_DIM_OF(int16_t);
        SPECIALIZE_DIM_OF(int32_t);
        SPECIALIZE_DIM_OF(int64_t);
        SPECIALIZE_DIM_OF(uint8_t);
        SPECIALIZE_DIM_OF(uint16_t);
        SPECIALIZE_DIM_OF(uint32_t);
        SPECIALIZE_DIM_OF(uint64_t);
        SPECIALIZE_DIM_OF(float);
        SPECIALIZE_DIM_OF(double);
        SPECIALIZE_DIM_OF(std::complex<float>);
        SPECIALIZE_DIM_OF(std::complex<double>);
#undef SPECIALIZE_DIM_OF

        template<class T, size_t N>
            struct dim_of<types::array<T,N>> {
                static const size_t value = 1 + dim_of<T>::value;
            };


        /* generic function to copy an array to another
         * implements array broadcasting in addition to regular copy
         */
        template<class E, class F>
            E& broadcast_copy(E& self, F const& other, utils::int_<0>) {
#ifdef _OPENMP
                size_t n = self.end() - self.begin();
                #pragma omp parallel for if(n>=PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
                for(size_t i = 0; i< n; ++i)
                    self[i] = other[i];
#else
                std::copy(other.begin(), other.end(), self.begin());
#endif
                return self;
            }
        template<class E, class F, size_t N>
            E& broadcast_copy(E& self, F const& other, utils::int_<N>) {
#ifdef _OPENMP
                size_t n = self.end() - self.begin();
                #pragma omp parallel for if(n>=PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
                for(size_t i = 0; i< n; ++i)
                    self[i] = other;
#else
                std::fill(self.begin(), self.end(), other);
#endif
                return self;
            }

    }

}

#endif
