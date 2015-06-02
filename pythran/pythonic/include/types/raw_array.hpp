#ifndef PYTHONIC_INCLUDE_TYPES_RAW_ARRAY_HPP
#define PYTHONIC_INCLUDE_TYPES_RAW_ARRAY_HPP

namespace pythonic
{

  namespace types
  {
    /* Wrapper class to store an array pointer
     *
     * for internal use only, meant to be stored in a shared_ptr
     */
    template <class T>
    class raw_array
    {
      raw_array(raw_array<T> const &) = delete;

    public:
      using pointer_type = T *;

      T *data;
      raw_array();
      raw_array(size_t n);
      raw_array(T *d);
      raw_array(raw_array<T> &&d);

      ~raw_array();
    };
  }
}

#endif
