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

// create a proxy named from `s' using function `f' in namespace `ns'
#define FPROXY_DECL(ns, s, f) \
    namespace proxy {\
        struct s {\
            typedef void callable;\
            template<typename... Types>\
            auto operator()(Types &&... types) const \
            -> decltype(ns::f(std::forward<Types>(types)...));\
        };\
    }

#define FPROXY_IMPL(ns, s, f) \
    namespace proxy {\
        template<typename... Types>\
            auto s::operator()(Types &&... types) const \
            -> decltype(ns::f(std::forward<Types>(types)...))\
            {\
                return ns::f(std::forward<Types>(types)...); \
            }\
    }

// create a proxy named from `f' using function `f' in namespace `ns'
#define PROXY(ns,f) FPROXY(ns, f, f)
#define PROXY_DECL(ns,f) FPROXY_DECL(ns, f, f)
#define PROXY_IMPL(ns,f) FPROXY_IMPL(ns, f, f)

// create a function named `f' from function `g'
#define ALIAS_DECL(f, g) template <class... Types> auto f(Types &&... args) -> decltype(g(std::forward<Types>(args)...));
#define ALIAS(f, g) template <class... Types> auto f(Types &&... args) -> decltype(g(std::forward<Types>(args)...)) { return g(std::forward<Types>(args)...); }



#endif
