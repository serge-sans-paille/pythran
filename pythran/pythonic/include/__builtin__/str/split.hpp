#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_SPLIT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_SPLIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            types::list<types::str> split(types::str const& in, types::str const& sep = " \n", long maxsplit = -1);

            types::list<types::str> split(types::str const& s, types::none_type const&, long maxsplit = -1);

            PROXY_DECL(pythonic::__builtin__::str, split);

        }

    }

}
#endif
