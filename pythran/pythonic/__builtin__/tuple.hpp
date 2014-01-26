#ifndef PYTHONIC_BUILTIN_TUPLE_HPP
#define PYTHONIC_BUILTIN_TUPLE_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/tuple.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            struct _tuple {
                types::list<typename Iterable::value_type> operator()(Iterable i) {
                    return types::list<typename Iterable::value_type>(i.begin(), i.end());
                }
            };

        template <class T>
            struct _tuple<types::list<T>> {
                types::list<T> operator()(types::list<T> i) {
                    return types::list<T>(i.begin(), i.end());
                }
            };
        template <class Iterable> /* this is far from perfect, but how to cope with the difference between python tuples and c++ ones ? */
            types::list<typename Iterable::iterator::value_type> tuple(Iterable i) {
                return _tuple<Iterable>()(i);
            }

        PROXY(pythonic::__builtin__, tuple);

    }

}
#endif
