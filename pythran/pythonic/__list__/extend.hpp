#ifndef PYTHONIC_LIST_EXTEND_HPP
#define PYTHONIC_LIST_EXTEND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __list__ {
        template<class T, class F>
            types::none_type extend(types::list<T> &seq, types::list<F> const& add) {
                seq+=add;
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, extend);

    }

}

#endif

