#ifndef PYTHONIC_TYPES_FLOAT_HPP
#define PYTHONIC_TYPES_FLOAT_HPP

#include "pythonic/types/attr.hpp"

namespace pythonic {
    namespace __builtin__ {
        template <size_t AttributeID>
            double getattr( double self) {
                return AttributeID == pythonic::types::attr::REAL ? self : 0.;
            }
    }
}

#endif
