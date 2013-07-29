#ifndef PYTHONIC_STR_RSTRIP_HPP
#define PYTHONIC_STR_RSTRIP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __str__ {
        types::str rstrip(types::str const& self, types::str const& to_del = " ")
        {
            return types::str(self.begin(), self.begin() + self.find_last_not_of(to_del) + 1);
        }
        PROXY(pythonic::__str__, rstrip);

    }

}

#endif

