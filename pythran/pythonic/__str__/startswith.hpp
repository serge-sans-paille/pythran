#ifndef PYTHONIC_STR_STARTSWITH_HPP
#define PYTHONIC_STR_STARTSWITH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        bool startswith(types::str const& s, types::str const& prefix, long start=0, size_t end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            return (end - start) >= prefix.size() and s.compare(start, prefix.size(), prefix) == 0;
        }

        PROXY(pythonic::__str__, startswith);
    }

}

#endif

