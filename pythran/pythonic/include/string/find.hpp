#ifndef PYTHONIC_INCLUDE_STRING_FIND_HPP
#define PYTHONIC_INCLUDE_STRING_FIND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace string {

        template<class T>
            auto find(types::str const& s, T&& val)
            -> decltype(s.find(std::forward<T>(val)));

        PROXY_DECL(pythonic::string, find);

    }

}

#endif
