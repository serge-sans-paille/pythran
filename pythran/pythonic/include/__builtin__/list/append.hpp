#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_APPEND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_APPEND_HPP

#include "pythonic/types/none.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace  list {

            template<class T, class F>
                types::none_type append(types::list<T> &seq, F const& value);

            template<class T, class F>
                types::none_type append(types::list<T> &seq, F&& value);

            template<class F>
                types::none_type append(types::empty_list &seq, F&& value);

            PROXY_DECL(pythonic::__builtin__::list, append);

        }

    }
}
#endif
