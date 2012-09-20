#ifndef PYTHONIC_UTILS_H
#define PYTHONIC_UTILS_H

//Use when the C/C++ function do not have the same name
//than in python
#define WRAP(type,name,cname,argType)\
    type name(argType x){ return cname(x); }

// Use this to create a proxy on a specific intrinsic
// should check out perfect forwarding too ...
#define PROXY(ns,f) \
    namespace proxy {\
        struct f {\
            template<typename... Types>\
                auto operator()(Types const &... types) -> decltype(ns::f(types...)) {\
                    return ns::f(types...); \
                }\
        };\
    }

#define VPROXY(ns,f) \
    namespace proxy {\
        struct f {\
            template<typename... Types>\
                auto operator()(Types &&... types) -> decltype(ns::f(types...)) {\
                    return ns::f(types...); \
                }\
        };\
    }

namespace pythonic {

    /* some constants ... */
    const bool True = true;
    const bool False = false;

    // container trait
    // from http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles/4410310#4410310
    template <typename T> struct is_container {
        template <typename U>
            static char test(U* u, int (*)[sizeof(typename U::const_iterator()==((U*)0)->begin())] = 0, int (*)[sizeof(typename U::const_iterator()==((U*)0)->end())] = 0);
        template <typename U> static long test(...);

        enum { value = (1 == sizeof test<T>(0)) };
    };

    template<class T>
        struct comparable_iterator:T {
            comparable_iterator() : T() {}
            comparable_iterator(T const & t) : T(t) {}
            bool operator<(comparable_iterator<T> other) {
                return (*this)!= other;
            }
        };

}
#endif
