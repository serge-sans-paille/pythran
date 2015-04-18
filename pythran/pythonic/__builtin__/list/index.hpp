#ifndef PYTHONIC_BUILTIN_LIST_INDEX_HPP
#define PYTHONIC_BUILTIN_LIST_INDEX_HPP

#include "pythonic/include/__builtin__/list/index.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {
            //TODO: have to raise a valueError
            template<class T>
                long index(types::list<T> &seq, T const& x)
                {
                    return seq.index(x);
                }

            template<class T>
                long index(types::list<T> &&seq, T const& x)
                {
                    return seq.index(x);
                }

            PROXY_IMPL(pythonic::__builtin__::list, index);

        }

    }

}
#endif
