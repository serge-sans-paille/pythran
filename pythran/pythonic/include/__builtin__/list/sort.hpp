#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_SORT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_SORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            template<class T>
                types::none_type sort(types::list<T> &seq);

            PROXY_DECL(pythonic::__builtin__::list, sort);

        }

    }

}
#endif
