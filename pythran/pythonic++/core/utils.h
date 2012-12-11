#ifndef PYTHONIC_UTILS_H
#define PYTHONIC_UTILS_H

//Use when the C/C++ function do not have the same name
//than in python
#define WRAP(type,name,cname,argType)\
    type name(argType x){ return cname(x); }

// Use this to create a proxy on a specific intrinsic
#define PROXY(ns,f) \
    namespace proxy {\
        struct f {\
            typedef void callable;\
            template<typename... Types>\
            auto operator()(Types &&... types) -> decltype(ns::f(std::forward<Types>(types)...)) {\
                return ns::f(std::forward<Types>(types)...); \
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

    /* callable trait { */

    template<typename T>
        struct is_callable
        {
            typedef char	yes;
            typedef struct { char _[2]; } no;

            template <class C> static yes _test(typename C::callable*);
            template <class C> static no _test(...);
            static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
        };

    /* } */

    /* iterable trait { */
    template<typename T>
        struct is_iterable
        {
            typedef char	yes;
            typedef struct { char _[2]; } no;

            template <class C> static yes _test(typename C::iterator*);
            template <class C> static no _test(...);
            static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
        };
    /* } */

    /* helper that retreives the nth type of a variadic template { */
    template<int id, class Type, class... Types>
        struct nth {
            typedef typename nth<id-1, Types...>::type type;
        };

    template<class Type, class... Types>
        struct nth<0, Type, Types...> {
            typedef Type type;
        };
    /* } */

    template<int> struct int_{}; // compile-time counter


    template<typename... Types>
        void fwd(Types const&... types) {
        }

}
#endif
