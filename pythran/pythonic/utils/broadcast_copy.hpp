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


        /* generic function to copy an array to another
         * implements array broadcasting in addition to regular copy
         */
        template<class E, class F>
            E& broadcast_copy(E& self, F const& other, utils::int_<0>) {
#ifdef _OPENMP
                size_t n = self.end() - self.begin();
                if(n>=PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
                {
                    #pragma omp parallel for
                    for(size_t i = 0; i< n; ++i)
                        self[i] = other[i];
                }
                else
                    std::copy(other.begin(), other.end(), self.begin());
#else
                std::copy(other.begin(), other.end(), self.begin());
#endif
                return self;
            }
        template<class E, class F, size_t N>
            E& broadcast_copy(E& self, F const& other, utils::int_<N>) {
#ifdef _OPENMP
                size_t n = self.end() - self.begin();
                if(n>=PYTHRAN_OPENMP_MIN_ITERATION_COUNT)
                {
                #pragma omp parallel for
                for(size_t i = 0; i< n; ++i)
                    self[i] = other;
                }
                else
                    std::fill(self.begin(), self.end(), other);
#else
                std::fill(self.begin(), self.end(), other);
#endif
                return self;
            }

    }

}

#endif
