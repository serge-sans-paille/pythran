#ifndef PYTHONIC_BUILTIN_IN_HPP
#define PYTHONIC_BUILTIN_IN_HPP

#include "pythonic/types/traits.hpp"
#include <algorithm>

namespace pythonic {

    template<class T, class V, bool F>
        struct _in {
            bool operator()(T t, V const& v) const {
                return std::find(t.begin(), t.end(), v) != t.end();
            }
        };
    template<class T, class V>
        struct _in<T, V, true> {
            bool operator()(T t, V const& v) const {
                return t.contains(v);
            }
        };

    template <class T, class V>
        bool in(T &&t, V const &v) {
            return _in<T, V, types::has_contains<typename std::remove_cv<typename std::remove_reference<T>::type>::type, V>::value>()(std::forward<T>(t), v);
        }

}

#endif

