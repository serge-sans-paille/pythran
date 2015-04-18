#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_EXTEND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_EXTEND_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            template<class T, class F>
                types::none_type
                extend(types::list<T> &seq, types::list<F> const& add);

            PROXY_DECL(pythonic::__builtin__::list, extend);

        }

    }

}
#endif
