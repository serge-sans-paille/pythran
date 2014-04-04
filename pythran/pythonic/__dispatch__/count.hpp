#ifndef PYTHONIC_DISPATCH_COUNT_HPP
#define PYTHONIC_DISPATCH_COUNT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template <class Any, class Value>
            auto count(Any&& any, Value&& value)
            -> decltype(any.count(std::forward<Value>(value)))
            {
                return any.count(std::forward<Value>(value));
            }
        PROXY(pythonic::__dispatch__, count);
    }
}

#endif
