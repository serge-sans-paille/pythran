#ifndef PYTHONIC_LIST_REVERSE_HPP
#define PYTHONIC_LIST_REVERSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"

namespace pythonic { namespace __builtin__  {

    namespace list {
        template<class T>
            types::none_type reverse(types::list<T> &seq) {
                std::reverse(seq.begin(),seq.end());
                return __builtin__::None;
            }

        PROXY(pythonic::__builtin__::list,reverse);

    }

}

}
#endif

