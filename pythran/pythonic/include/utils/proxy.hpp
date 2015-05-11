#ifndef PYTHONIC_INCLUDE_UTILS_PROXY_HPP
#define PYTHONIC_INCLUDE_UTILS_PROXY_HPP

#include <utility>

// create a proxy named from `s' using function `f' in namespace `ns'
#define FPROXY_DECL(ns, s, f)                                                   \
    namespace proxy {                                                           \
        struct s {                                                              \
            using callable = void;                                              \
            template<typename... Types>                                         \
                auto operator()(Types &&... types) const                        \
                -> decltype(ns::f(std::forward<Types>(types)...));              \
        };                                                                      \
    }

// create a proxy named from `f' using function `f' in namespace `ns'
#define PROXY_DECL(ns,f) FPROXY_DECL(ns, f, f)

// create a function named `f' from function `g'
#define ALIAS_DECL(f, g)                                                        \
    template <class... Types>                                                   \
        auto f(Types &&... args) -> decltype(g(std::forward<Types>(args)...));

#endif
