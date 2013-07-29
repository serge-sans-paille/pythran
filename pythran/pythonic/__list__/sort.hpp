#ifndef PYTHONIC_LIST_SORT_HPP
#define PYTHONIC_LIST_SORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __list__ {
        template<class T>
            types::none_type sort(types::list<T> &seq) {
                std::sort(seq.begin(),seq.end());
                return __builtin__::None;
            }

        PROXY(pythonic::__list__,sort);

    }

}

#endif

