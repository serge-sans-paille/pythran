#ifndef PYTHONIC_UTILS_NESTED_CONTAINER_HPP
#define PYTHONIC_UTILS_NESTED_CONTAINER_HPP

#include "pythonic/include/utils/nested_container.hpp"

#include <limits>
#include "pythonic/types/traits.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic
{
  namespace utils
  {

    template <class T>
    size_t nested_container_size<T>::flat_size(T const &t)
    {
      return t.size() *
             nested_container_size<typename std::conditional<
                 // If we have a scalar of a complex, we want to stop
                 // recursion, and then dispatch to bool specialization
                 types::is_dtype<typename Type::value_type>::value, bool,
                 typename Type::value_type>::type>::flat_size(*t.begin());
    }

    /* Recursion stops on bool */
    template <class F>
    constexpr size_t nested_container_size<bool>::flat_size(F)
    {
      return 1;
    }
  }
}

#endif
