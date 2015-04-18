#ifndef PYTHONIC_BUILTIN_STR_STARTSWITH_HPP
#define PYTHONIC_BUILTIN_STR_STARTSWITH_HPP

#include "pythonic/include/__builtin__/str/startswith.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            bool
            startswith(types::str const& s, types::str const& prefix, long start, long end)
            {
                if(end < 0)
                    end += s.size();
                return (end - start) >= static_cast<long>(prefix.size()) and s.compare(start, prefix.size(), prefix) == 0;
            }

            bool
            startswith(types::str const& s, types::str const& prefix, long start)
            {
                return startswith(s, prefix, start, s.size());
            }


            PROXY_IMPL(pythonic::__builtin__::str, startswith);
        }

    }

}
#endif

