#ifndef PYTHRAN_PYTHONIC_UTILS_PROXY_HPP
#define PYTHRAN_PYTHONIC_UTILS_PROXY_HPP

#include <utility>

// create a proxy named from `s' using function `f' in namespace `ns'
#define FPROXY(ns, s, f) \
    namespace proxy {\
        struct s {\
            typedef void callable;\
            template<typename... Types>\
            auto operator()(Types &&... types) const \
            -> decltype(ns::f(std::forward<Types>(types)...))\
            {\
                return ns::f(std::forward<Types>(types)...); \
            }\
        };\
    }

// create a proxy named from `f' using function `f' in namespace `ns'
#define PROXY(ns,f) FPROXY(ns, f, f)

// create a function named `f' from function `g'
#define ALIAS(f, g) template <class... Types> auto f(Types &&... args) -> decltype(g(std::forward<Types>(args)...)) { return g(std::forward<Types>(args)...); }



#endif
