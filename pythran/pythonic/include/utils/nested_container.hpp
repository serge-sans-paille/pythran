#ifndef PYTHONIC_INCLUDE_UTILS_NESTED_CONTAINER_HPP
#define PYTHONIC_INCLUDE_UTILS_NESTED_CONTAINER_HPP

#include <limits>
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

namespace pythonic
{
  namespace types
  {
    template <class T>
    class list;
    template <class T, size_t N>
    struct array;
  }

  namespace utils
  {

    /* compute nested container depth and memory size*/
    template <class T, bool IsArray>
    struct nested_container_depth_helper;

    template <class T>
    struct nested_container_depth_helper<T, false> {
      static const int value = 0;
    };

    template <class T>
    struct nested_container_depth_helper<T, true> {
      static const int value = T::value;
    };

    template <class T>
    struct nested_container_depth {
      static const int value =
          nested_container_depth_helper<T, types::is_array<T>::value>::value;
    };

    template <class T>
    struct nested_container_depth<types::list<T>> {
      static const int value = 1 + nested_container_depth<T>::value;
    };

    template <class T, size_t N>
    struct nested_container_depth<types::array<T, N>> {
      static const int value = 1 + nested_container_depth<T>::value;
    };

    template <class T, size_t N>
    struct nested_container_depth<types::ndarray<T, N>> {
      static const int value = N;
    };

    /* Get the size of a container, using recursion on inner container if any
     * FIXME: should be a constexpr?
     * FIXME: why a class and not a function?
     */
    template <class T>
    struct nested_container_size {
      using Type = typename std::remove_cv<
          typename std::remove_reference<T>::type>::type;
      static size_t flat_size(T const &t);
    };

    /* Recursion stops on bool */
    template <>
    struct nested_container_size<bool> {
      template <class F>
      constexpr static size_t flat_size(F);
    };

    /* Statically define (by recursion) the type of element inside nested
     * containers */
    template <class T, bool IsArray>
    struct nested_container_value_type_helper;

    template <class T>
    struct nested_container_value_type_helper<T, false> {
      using type = T;
    };

    template <class T>
    struct nested_container_value_type_helper<T, true> {
      using type = typename T::dtype;
    };

    template <class T>
    struct nested_container_value_type {
      using type = typename nested_container_value_type_helper<
          T, types::is_array<T>::value>::type;
    };

    template <class T>
    struct nested_container_value_type<types::list<T>> {
      using type = typename nested_container_value_type<T>::type;
    };

    template <class T, size_t N>
    struct nested_container_value_type<types::array<T, N>> {
      using type = typename nested_container_value_type<T>::type;
    };

    template <class T, size_t N>
    struct nested_container_value_type<types::ndarray<T, N>> {
      using type = T;
    };
  }
}

#endif
