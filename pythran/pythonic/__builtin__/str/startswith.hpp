#ifndef PYTHONIC_BUILTIN_STR_STARTSWITH_HPP
#define PYTHONIC_BUILTIN_STR_STARTSWITH_HPP

#include "pythonic/include/__builtin__/str/startswith.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            bool
            startswith(types::str const& s, types::str const& prefix, long start, size_t end)
            {
                if(end == std::string::npos)
                    end = s.size();
                return (end - start) >= prefix.size() and s.compare(start, prefix.size(), prefix) == 0;
            }

            PROXY_IMPL(pythonic::__builtin__::str, startswith);
        }

    }

}
#endif

