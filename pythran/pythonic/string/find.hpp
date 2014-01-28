#ifndef PYTHONIC_STRING_FIND_HPP
#define PYTHONIC_STRING_FIND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace string {

        template<class T>
            auto find(types::str const& s, T&& val) -> decltype(s.find(std::forward<T>(val))) {
                return s.find(std::forward<T>(val));
            }
        PROXY(pythonic::string, find);

    }

}

#endif

