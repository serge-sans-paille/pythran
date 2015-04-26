#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_INSERT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_INSERT_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            template<class T, class F>
                types::none_type
                insert(types::list<T> &seq, long n, F const& value);

            template<class T, class F>
                types::none_type
                insert(types::list<T> &seq, long n, F && value);

            PROXY_DECL(pythonic::__builtin__::list, insert);

        }

    }

}
#endif
