#ifndef PYTHONIC_STR_ISALPHA_HPP
#define PYTHONIC_STR_ISALPHA_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic { namespace __builtin__  {

    namespace str {
        using std::isalpha;

        bool isalpha(types::str const& s) {
            return not s.empty() and std::all_of(s.begin(), s.end(), (int (*)(int))std::isalpha);
        }
        PROXY(pythonic::__builtin__::str, isalpha);

    }
}
}
#endif

