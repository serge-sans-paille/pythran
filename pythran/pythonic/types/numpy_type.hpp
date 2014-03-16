#ifndef PYTHONIC_TYPES_NUMPYTYPE_HPP
#define PYTHONIC_TYPES_NUMPYTYPE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace types {

        template<class T>
            struct numpy_type {
                typedef decltype(std::declval<T>()()) type;
            };
#define SPECIALIZE_NUMPY_TYPE(TYPE) template<> struct numpy_type<TYPE> { typedef TYPE type; }
        SPECIALIZE_NUMPY_TYPE(bool);
        SPECIALIZE_NUMPY_TYPE(int8_t);
        SPECIALIZE_NUMPY_TYPE(int16_t);
        SPECIALIZE_NUMPY_TYPE(int32_t);
        SPECIALIZE_NUMPY_TYPE(int64_t);
        SPECIALIZE_NUMPY_TYPE(uint8_t);
        SPECIALIZE_NUMPY_TYPE(uint16_t);
        SPECIALIZE_NUMPY_TYPE(uint32_t);
        SPECIALIZE_NUMPY_TYPE(uint64_t);
        SPECIALIZE_NUMPY_TYPE(float);
        SPECIALIZE_NUMPY_TYPE(double);
        SPECIALIZE_NUMPY_TYPE(std::complex<float>);
        SPECIALIZE_NUMPY_TYPE(std::complex<double>);
#undef SPECIALIZE_NUMPY_TYPE
    }

}

#endif

