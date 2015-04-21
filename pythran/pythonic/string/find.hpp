#ifndef PYTHONIC_STRING_FIND_HPP
#define PYTHONIC_STRING_FIND_HPP

#include "pythonic/include/string/find.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace string {

        template<class T>
            long find(types::str const& s, T&& val)
            {
                return s.find(std::forward<T>(val));
            }

        PROXY_IMPL(pythonic::string, find);

    }

}

#endif
