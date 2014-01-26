#ifndef PYTHONIC_STR_SPLIT_HPP
#define PYTHONIC_STR_SPLIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

#include "pythonic/__str__/strip.hpp"

namespace pythonic {

    namespace __str__ {
        types::list<types::str> split(types::str const& in, types::str const& sep = " \n", long maxsplit = -1)
        {
            types::str s = strip(in);
            types::list<types::str> res(0);
            size_t current = 0;
            size_t next = 0;
            long numsplit = 0;
            while (next != types::str::npos && (numsplit++<maxsplit || maxsplit==-1))
            {
                next = s.find_first_of( sep, current );
                res.push_back(s.substr( current, next - current ));
                current = next + 1;
            }
            if(next != types::str::npos)
            {
                current = next + 1;
                res.push_back(s.substr( current, s.size() - current ));    
            }
            return res;
        } 

        types::list<types::str> split(types::str const& s, types::none_type const&, long maxsplit = -1)
        {
            return split(s, " ", maxsplit);
        } 
        PROXY(pythonic::__str__, split);

    }

}

#endif

