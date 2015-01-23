#ifndef PYTHONIC_TYPES_TRAITS_HPP
#define PYTHONIC_TYPES_TRAITS_HPP

namespace std {
template <class T> class complex;
}

namespace pythonic {

    namespace types {

        /* could overload is_scalar to consider complex has scalar types */
        template<class T>
            struct is_complex {
                static constexpr bool value = false;
                typedef T type;
            };
        template<class T>
            struct is_complex<std::complex<T>> {
                static constexpr bool value = true;
                typedef T type;
            };

#define MEMBER_TYPE_TRAIT(check_struct, member)\
        template<typename T>\
            struct check_struct\
            {\
                typedef char yes;\
                typedef struct { char _[2]; } no;\
                template <class C> static yes _test(typename C::member*);\
                template <class C> static no _test(...);\
                static const bool value = sizeof( _test<typename std::remove_reference<T>::type>(nullptr)) == sizeof(yes);\
            };

#define MEMBER_ATTR_TRAIT(check_struct, member)\
        template<typename T>\
            struct check_struct\
            {\
                typedef char yes;\
                typedef struct { char _[2]; } no;\
                template <class C> static yes _test(decltype(&C::member));\
                template <class C> static no _test(...);\
                static const bool value = sizeof( _test<typename std::remove_reference<T>::type>(nullptr)) == sizeof(yes);\
            };

        /* trait to check if a type is iterable*/
        MEMBER_TYPE_TRAIT(is_iterable, iterator);

        /* trait to check if a type is callable */
        MEMBER_TYPE_TRAIT(is_callable, callable);

        /* trait to check if a type is pure */
        MEMBER_TYPE_TRAIT(is_pure, pure);

        /* trait to check if the type has a size member */
        MEMBER_ATTR_TRAIT(has_size, size);

        /* trait to check if the type has a contains member */
        template<typename T, class V>\
            struct has_contains\
            {\
                typedef char yes;\
                typedef struct { char _[2]; } no;\
                template <class C> static yes _test(decltype(&C::contains));\
                template <class C> static yes _test(decltype(&C::template contains<V>));
                template <class C> static no _test(...);\
                static const bool value = sizeof( _test<typename std::remove_reference<T>::type>(nullptr)) == sizeof(yes);\
            };

        /* trait to check if the type has a shape member */
        MEMBER_ATTR_TRAIT(has_shape, shape);

        /* trait to check if the type has a static size */
        template<class T>
            struct len_of {
                static long constexpr value = -1;
            };
    }
}

#endif
