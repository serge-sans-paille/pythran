#ifndef PYTHONIC_BUILTIN_STR_LSTRIP_HPP
#define PYTHONIC_BUILTIN_STR_LSTRIP_HPP

#include "pythonic/include/__builtin__/str/lstrip.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::str lstrip(types::str const& self, types::str const& to_del)
            {
                return types::str(self.begin() + self.find_first_not_of(to_del), self.end());
            }

            PROXY_IMPL(pythonic::__builtin__::str, lstrip);
        }

    }

}
#endif

