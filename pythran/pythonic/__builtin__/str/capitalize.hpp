#ifndef PYTHONIC_BUILTIN_STR_CAPITALIZE_HPP
#define PYTHONIC_BUILTIN_STR_CAPITALIZE_HPP

#include "pythonic/include/__builtin__/str/capitalize.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::str capitalize(types::str const & s)
            {
                if(s.empty())
                    return s;
                else {
                    types::str copy = s;
                    copy[0] = ::toupper(s[0]);
                    std::transform(s.begin()+1, s.end(), copy.begin()+1, ::tolower);
                    return copy;
                }
            }

            PROXY_IMPL(pythonic::__builtin__::str, capitalize);

        }

    }

}
#endif
