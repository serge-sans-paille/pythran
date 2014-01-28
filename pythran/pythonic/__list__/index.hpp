#ifndef PYTHONIC_LIST_INDEX_HPP
#define PYTHONIC_LIST_INDEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __list__ {
        //TODO: have to raise a valueError
        template<class T>
            long index(types::list<T> &seq, T const& x) {
                return seq.index(x);
            }
        template<class T>
            long index(types::list<T> &&seq, T const& x) {
                return seq.index(x);
            }
        PROXY(pythonic::__list__, index);

    }

}

#endif

