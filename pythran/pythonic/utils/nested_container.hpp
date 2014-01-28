#ifndef PYTHONIC_UTILS_NESTED_CONTAINER_HPP
#define PYTHONIC_UTILS_NESTED_CONTAINER_HPP

#include <limits>
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace utils {


        /* compute nested container depth and memory size*/
        template<class T>
            struct nested_container_depth {
                static const int value = 1 + nested_container_depth<
                    typename std::conditional<
                    types::is_iterable<typename std::remove_reference<T>::type>::value,
                    typename std::conditional<
                        std::is_scalar<typename std::remove_reference<T>::type::value_type>::value or types::is_complex<typename std::remove_reference<T>::type::value_type>::value,
                    bool,
                    typename std::remove_reference<T>::type::value_type
                        >::type,
                    bool
                        >::type
                        >::value;
            };
        template<>
            struct nested_container_depth<bool> {
                static const int value = 0;
            };


        /* Get the size of a container, using recursion on inner container if any
         * FIXME: should be a constexpr?
         * FIXME: why a class and not a function?
         */
        template<class T>
            struct nested_container_size {
                typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type Type;
                static size_t size(T const& t) {
                    return t.size()
                        *
                        nested_container_size<
                        typename std::conditional<
                        // If we have a scalar of a complex, we want to stop
                        // recursion, and then dispatch to bool specialization
                        std::is_scalar<typename Type::value_type>::value
                        or types::is_complex<typename Type::value_type>::value,
                           bool,
                           typename Type::value_type
                               >::type
                               >::size(*t.begin());
                }
            };
        /* Recursion stops on bool */
        template<>
            struct nested_container_size<bool> {
                template<class F>
                    static size_t size(F) { return 1; }
            };

        /* Statically define (by recursion) the type of element inside nested constainers */
        template<class T, size_t end=std::numeric_limits<size_t>::max()>
            struct nested_container_value_type {
                typedef typename nested_container_value_type<typename T::value_type, ((std::is_scalar<typename T::value_type>::value or types::is_complex<typename T::value_type>::value)?0:end-1)>::type type;
            };
        template<class T>
            struct nested_container_value_type<T,0> {
                typedef T type;
            };

    }

}

#endif
