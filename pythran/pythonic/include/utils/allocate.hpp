#ifndef PYTHONIC_INCLUDE_UTILS_ALLOCATE_HPP
#define PYTHONIC_INCLUDE_UTILS_ALLOCATE_HPP

#include <cstdlib>

PYTHONIC_NS_BEGIN

namespace utils
{
  template <class T>
  inline T *allocate(size_t nmemb)
  {
    return (T *)malloc(sizeof(T) * nmemb);
  }

  template <class T>
  inline T *callocate(size_t nmemb)
  {
    return (T *)calloc(nmemb, sizeof(T));
  }

  template <class T>
  inline T *reallocate(T *prev, size_t nmemb)
  {
    return (T *)realloc(prev, sizeof(T) * nmemb);
  }

  template <class T>
  inline void deallocate(T *mem)
  {
    free(mem);
  }

  template <class T>
  struct allocator {
    typedef T value_type;

    allocator() = default;

    template <class U>
    constexpr allocator(const allocator<U> &) noexcept
    {
    }

    [[nodiscard]] T *allocate(std::size_t n)
    {
      return ::pythonic::utils::allocate<T>(n);
    }

    void deallocate(T *p, std::size_t) noexcept
    {
      ::pythonic::utils::deallocate(p);
    }

    template <class U>
    constexpr bool operator==(const allocator<U> &) const
    {
      return true;
    }

    template <class U>
    constexpr bool operator!=(const allocator<U> &) const
    {
        return false;
  }
}; // namespace utils

} // namespace utils
PYTHONIC_NS_END

#endif
