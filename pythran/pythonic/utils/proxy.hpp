#ifndef PYTHONIC_UTILS_PROXY_HPP
#define PYTHONIC_UTILS_PROXY_HPP

#include "pythonic/include/utils/proxy.hpp"

#include <utility>

#define FPROXY_IMPL(ns, s, f)                                                   \
    namespace proxy {                                                           \
        template<typename... Types>                                             \
            auto s::operator()(Types &&... types) const                         \
            -> decltype(ns::f(std::forward<Types>(types)...))                   \
            {                                                                   \
                return ns::f(std::forward<Types>(types)...);                    \
            }                                                                   \
    }

// create a proxy named from `f' using function `f' in namespace `ns'
#define PROXY_IMPL(ns,f) FPROXY_IMPL(ns, f, f)

// create a function named `f' from function `g'
#define ALIAS(f, g)                                                             \
    template <class... Types>                                                   \
        auto f(Types &&... args) -> decltype(g(std::forward<Types>(args)...))   \
        {                                                                       \
            return g(std::forward<Types>(args)...);                             \
        }

#endif
