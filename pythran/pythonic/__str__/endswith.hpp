#ifndef PYTHONIC_STR_ENDSWITH_HPP
#define PYTHONIC_STR_ENDSWITH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        bool endswith(types::str const& s, types::str const& suffix, long start=0, size_t end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            long rstart = end - suffix.size();
            return rstart >= start and s.compare(rstart, suffix.size(), suffix) == 0;
        }
        PROXY(pythonic::__str__, endswith);

    }

}

#endif

