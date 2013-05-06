#ifndef PYTHONIC_UTILS_H
#define PYTHONIC_UTILS_H

#include <type_traits>
#include <iterator>
#include <complex>

// overload is_scalar to consider complex has scalar types
template<class T>
struct is_complex {
    static const bool value = false;
};
template<class T>
struct is_complex<std::complex<T>> {
    static const bool value = true;
};

//Use when the C/C++ function do not have the same name
//than in python
#define WRAP(type,name,cname,argType)\
    type name(argType x){ return cname(x); }

// Use to declare a function as an alias of another one
#define ALIAS(oldf, newf)\
    template<typename... Types>\
        auto newf(Types &&... types) ->  decltype(oldf(std::forward<Types>(types)...)) {\
            return oldf(std::forward<Types>(types)...);\
        }

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

// use this macro to make builtin class members available in the builtin namespace
#define BUILTIN_CLASS(name) \
    namespace __builtin__ { \
        namespace name { \
            namespace proxy {\
                using namespace ::pythonic::name::proxy;\
            }\
        }\
    }

namespace pythonic {

    /* some constants ... */
    const bool True = true;
    const bool False = false;

    // none trait
    template<class T> struct none;
    template<class T>
        struct is_none {
            static const bool value = false;
        };
    template<class T>
        struct is_none<none<T>> {
            static const bool value = true;
        };


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
            static const bool value = sizeof( _test<typename std::remove_reference<T>::type>(nullptr)) == sizeof(yes);
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

    template<size_t> struct int_{}; // compile-time counter


    template<typename... Types>
        void fwd(Types const&... types) {
        }
        
    /* Get the "minimum" of all iterators :
     - only random => random
     - at least one forward => forward 
    */
    template<typename... Iters>
        struct min_iterator;

    template<typename T>
        struct min_iterator<T> {typedef typename T::iterator_category type;};

    template<typename T, typename... Iters>
        struct min_iterator<T, Iters...> {typedef typename std::conditional<std::is_same<typename T::iterator_category, std::forward_iterator_tag>::value, std::forward_iterator_tag, typename pythonic::min_iterator<Iters...>::type >::type type;};

    /* compute nested container depth and memory size*/
    template<class T>
        struct nested_container_depth {
            static const int value = 1 + nested_container_depth<
                typename std::conditional<
                    is_iterable<T>::value,
                    typename std::conditional<
                        std::is_scalar<typename T::value_type>::value or is_complex<typename T::value_type>::value,
                        bool,
                        typename T::value_type
                    >::type,
                    bool
                >::type
            >::value;
        };
    template<>
        struct nested_container_depth<bool> {
            static const int value = 0;
        };

    template<class T>
        struct nested_container_size {
            typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type Type;
            size_t operator()(T const& t) {
                return t.size()
                    *
                    nested_container_size<
                    typename std::conditional<
                        std::is_scalar<typename Type::value_type>::value or is_complex<typename Type::value_type>::value,
                        bool,
                        typename Type::value_type
                    >::type>()(*t.begin());
            }
        };
    template<>
        struct nested_container_size<bool> {
            template<class F>
            size_t operator()(F) { return 1; }
        };
    template<class T, bool end=0>
        struct nested_container_value_type {
            typedef typename nested_container_value_type<typename T::value_type, std::is_scalar<typename T::value_type>::value or is_complex<typename T::value_type>::value >::type type;
        };
    template<class T>
        struct nested_container_value_type<T,true> {
            typedef T type;
        };


}
#endif
