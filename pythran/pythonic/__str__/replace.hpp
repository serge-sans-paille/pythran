#ifndef PYTHONIC_STR_REPLACE_HPP
#define PYTHONIC_STR_REPLACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str replace(types::str const& self, types::str const& old_pattern, types::str const& new_pattern, long count=std::numeric_limits<long>::max())
        {
            char const * needle = old_pattern.c_str();
            char const * new_needle = new_pattern.c_str();
            char const * new_needle_end = new_needle + new_pattern.size();
            char const * haystack = self.c_str();

            char const * haystack_next = strstr(haystack, needle);
            if(not count or not haystack_next) {
                return types::str(haystack);
            }
            else {
                size_t n = 1 + std::max(self.size(), self.size()* (1+new_pattern.size()) / (1+old_pattern.size()));
                char *buffer = new char[n];
                char *iter = buffer;
                do {
                    iter = std::copy(haystack, haystack_next, iter);
                    iter = std::copy(new_needle, new_needle_end, iter);
                    count -= 1;
                    haystack = haystack_next + old_pattern.size();
                    assert(size_t(iter - buffer) < n);
                } while(count and (haystack_next=strstr(haystack, needle)));
                std::copy(haystack, self.c_str() + self.size() + 1, iter);

                types::str replaced(buffer);
                delete [] buffer;
                return replaced;
            }

        }

        PROXY(pythonic::__str__, replace);

    }

}

#endif

