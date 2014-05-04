#ifndef PYTHONIC_STR_STRIP_HPP
#define PYTHONIC_STR_STRIP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str strip(types::str const& self, types::str const& to_del = " \n")
        {
            if(not self)
                return self;
            auto first = self.find_first_not_of(to_del);
            if(first == types::str::npos)
                return types::str();
            else {
            return types::str(self.begin() + first, self.begin() + self.find_last_not_of(to_del)+ 1);
            }
        }
        PROXY(pythonic::__str__, strip);

    }

}

#endif

