#ifndef PYTHONIC_BUILTIN_LIST_INSERT_HPP
#define PYTHONIC_BUILTIN_LIST_INSERT_HPP

#include "pythonic/include/__builtin__/list/insert.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace list {

            template<class T, class F>
                types::none_type
                insert(types::list<T> &seq, long n, F const& value)
                {
                    n = n % (1 + static_cast<long>(seq.size()));
                    if (n < 0)
                        n += seq.size();
                    seq.insert(n, value);
                    return __builtin__::None;
                }

            template<class T, class F>
                types::none_type
                insert(types::list<T> &seq, long n, F && value)
                {
                    n = n % (1 + static_cast<long>(seq.size())); // +1 because we want to be able to insert at the end of seq
                    if (n < 0)
                        n+=seq.size();
                    seq.insert(n, value);
                    return __builtin__::None;
                }

            PROXY_IMPL(pythonic::__builtin__::list, insert);

        }

    }

}
#endif
