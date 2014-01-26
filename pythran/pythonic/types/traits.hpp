#ifndef PYTHONIC_TYPES_TRAITS_HPP
#define PYTHONIC_TYPES_TRAITS_HPP

#include <complex>

namespace pythonic {

    namespace types {

        /* could overload is_scalar to consider complex has scalar types */
        template<class T>
            struct is_complex {
                static const bool value = false;
            };
        template<class T>
            struct is_complex<std::complex<T>> {
                static const bool value = true;
            };

        /* trait to check if a type is iterable { */
        template<typename T>
            struct is_iterable
            {
                typedef char yes;
                typedef struct { char _[2]; } no;

                template <class C> static yes _test(typename C::iterator*);
                template <class C> static no _test(...);
                static const bool value = sizeof( _test<typename std::remove_reference<T>::type>(nullptr)) == sizeof(yes);
            };

        /* trait to check if a type is callable */
        template<typename T>
            struct is_callable
            {
                typedef char yes;
                typedef struct { char _[2]; } no;

                template <class C> static yes _test(typename C::callable*);
                template <class C> static no _test(...);
                static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
            };

        /* trait to check if the type has a size member */
        template<typename T>
            struct has_size
            {
                typedef char yes;
                typedef struct { char _[2]; } no;

                template <class C> static yes _test(decltype(&C::size));
                template <class C> static no _test(...);
                static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
            };

        /* trait to check if the type has a contains member */
        template<typename T, typename V>
            struct has_contains
            {
                typedef char yes;
                typedef struct { char _[2]; } no;

                template <class C> static yes _test(decltype(&C::template contains<V>));
                template <class C> static yes _test(decltype(&C::contains));
                template <class C> static no _test(...);
                static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
            };
        /* trait to check if the type as a shape member { */

        template<typename T>
            struct has_shape
            {
                typedef char yes;
                typedef struct { char _[2]; } no;

                template <class C> static yes _test(decltype(std::declval<C>().shape)*);
                template <class C> static no _test(...);
                static const bool value = sizeof( _test<T>(nullptr)) == sizeof(yes);
            };

        /* } */

    }

    }

#endif
