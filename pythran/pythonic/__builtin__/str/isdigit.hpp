#ifndef PYTHONIC_STR_ISDIGIT_HPP
#define PYTHONIC_STR_ISDIGIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic { namespace __builtin__  {

    namespace str {
        using std::isdigit;

        bool isdigit(types::str const& s) {
            return not s.empty() and std::all_of(s.begin(), s.end(), (int (*)(int))std::isdigit);
        }
        PROXY(pythonic::__builtin__::str, isdigit);

    }
}
}
#endif
