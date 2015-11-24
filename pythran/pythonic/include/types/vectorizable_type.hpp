#ifndef PYTHONIC_INCLUDE_TYPES_VECTORIZABLE_TYPE_HPP
#define PYTHONIC_INCLUDE_TYPES_VECTORIZABLE_TYPE_HPP

namespace pythonic
{
  namespace types
  {

    template <class T>
    struct is_vectorizable {
      static const bool value =
          std::is_fundamental<T>::value and not std::is_same<T, bool>::value;
    };

    /* trait to check if is T is an array-like type that supports vectorization
    */
    template <class T, bool scalar = is_dtype<T>::value>
    struct is_vectorizable_array;

    template <class T>
    struct is_vectorizable_array<T, true> : std::false_type {
    };

    template <class T>
    struct is_vectorizable_array<T, false>
        : std::integral_constant<bool, T::is_vectorizable> {
    };

    template <class O>
    struct is_vector_op;
  }
}
#endif
