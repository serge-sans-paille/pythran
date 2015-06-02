#ifndef PYTHONIC_TYPES_RAW_ARRAY_HPP
#define PYTHONIC_TYPES_RAW_ARRAY_HPP

#include "pythonic/include/types/raw_array.hpp"

namespace pythonic
{

  namespace types
  {
    /* Wrapper class to store an array pointer
     *
     * for internal use only, meant to be stored in a shared_ptr
     */
    template <class T>
    raw_array<T>::raw_array()
        : data(nullptr)
    {
    }

    template <class T>
    raw_array<T>::raw_array(size_t n)
        : data((T *)malloc(sizeof(T) * n))
    {
    }

    template <class T>
    raw_array<T>::raw_array(T *d)
        : data(d)
    {
    }

    template <class T>
    raw_array<T>::raw_array(raw_array<T> &&d)
        : data(d.data)
    {
      d.data = nullptr;
    }

    template <class T>
    raw_array<T>::~raw_array()
    {
      if (data)
        free(data);
    }
  }
}

#endif
