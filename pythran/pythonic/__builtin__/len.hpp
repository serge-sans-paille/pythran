#ifndef PYTHONIC_BUILTIN_LEN_HPP
#define PYTHONIC_BUILTIN_LEN_HPP

#include "pythonic/types/traits.hpp"
#include "pythonic/utils/proxy.hpp"

#include <iterator>

namespace pythonic {

    namespace __builtin__ {

        template <class T, class I, bool F>
            struct _len {
                long operator()(T const &t) {
                    static_assert(!std::is_same<I, std::random_access_iterator_tag>::value, "WTF");
                    static_assert(!types::has_size<T>::value, "WTF2");
                    return 1;
                }
            };

        template <class T>
            struct _len<T, std::random_access_iterator_tag, false> {
                long operator()(T const &t) {
                    return std::distance(t.begin(), t.end());
                }
            };

        template <class T, class F>
            struct _len<T, F, true> {
                long operator()(T const &t) {
                    return t.size();
                }
            };

        template <class... Types>
            long len(std::tuple<Types...> const&) {
                return sizeof...(Types);
            }

        long len(char) {
            return 1;
        }

        template <class T>
            long len(T const &t) {
                return _len<T, typename std::iterator_traits<typename T::iterator>::iterator_category, types::has_size<T>::value>()(t);
            }

        PROXY(pythonic::__builtin__,len);

    }

}
#endif
