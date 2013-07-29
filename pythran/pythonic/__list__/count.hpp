#ifndef PYTHONIC_LIST_COUNT_HPP
#define PYTHONIC_LIST_COUNT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

#include <algorithm>

namespace pythonic {

    namespace __list__ {
        template<class T>
            long count(types::list<T> &seq, T const& x) {
                return std::count(seq.begin(),seq.end(),x);
            }

        template<class T>
            long count(types::list<T> &seq, T &&x) {
                return std::count(seq.begin(),seq.end(),std::forward<T>(x));
            }
        template<class T>
            long count(types::list<T> &&seq, T &&x) {
                return std::count(seq.begin(),seq.end(),std::forward<T>(x));
            }

        PROXY(pythonic::__list__,count);

    }

}

#endif

