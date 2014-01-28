#ifndef PYTHONIC_LIST_APPEND_HPP
#define PYTHONIC_LIST_APPEND_HPP

#include "pythonic/__builtin__/None.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace  __list__ {

        template<class T, class F>
            types::none_type append(types::list<T> &seq, F const& value) {
                seq.push_back(value);
                return __builtin__::None;
            }
        template<class T, class F>
            types::none_type append(types::list<T> &seq, F&& value) {
                seq.push_back(value);
                return __builtin__::None;
            }
        template<class F>
            types::none_type append(types::empty_list &seq, F&& value) {
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, append);

    }

}

#endif

