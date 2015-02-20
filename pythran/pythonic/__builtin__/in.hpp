#ifndef PYTHONIC_BUILTIN_IN_HPP
#define PYTHONIC_BUILTIN_IN_HPP

#include "pythonic/types/traits.hpp"
#include <algorithm>

namespace pythonic {

    template<bool has_contains> struct _in;
    template<>
        struct _in<false>{
          template<class T, class V>
            bool operator()(T&& t, V const& v) const {
                return std::find(t.begin(), t.end(), v) != t.end();
            }
        };
    template<>
        struct _in<true> {
          template<class T, class V>
            bool operator()(T&& t, V const& v) const {
                return t.contains(v);
            }
        };

    template <class T, class V>
        bool in(T &&t, V const &v) {
            using RT = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
            static bool constexpr has_contains = types::has_contains<RT, V>::value;
            return _in<has_contains>()(std::forward<T>(t), v);
        }

}

#endif

