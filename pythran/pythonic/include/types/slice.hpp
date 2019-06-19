#ifndef PYTHONIC_INCLUDE_TYPES_SLICE_HPP
#define PYTHONIC_INCLUDE_TYPES_SLICE_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/attr.hpp"

#include <limits>
#include <ostream>

PYTHONIC_NS_BEGIN

namespace types
{

  template <class T>
  class bound
  {
    T value_;

    // use a sentinel to store none<long>, it takes less space
    static constexpr long sentinel = std::numeric_limits<T>::min();

  public:
    bound() = default;
    bound(none_type) : value_(sentinel)
    {
    }
    bound(none<T> v) : value_(v.is_none ? sentinel : (T)v)
    {
    }
    bound(T v) : value_(v)
    {
    }

    operator T() const
    {
      return value_;
    }
    operator none<T>() const
    {
      if (value_ == sentinel)
        return none_type();
      else
        return value_;
    }
    bool is_none() const
    {
      return value_ == sentinel;
    }
  };

  struct slice;
  template <class L, class U>
  struct contiguous_slice;

  template <class T>
  struct is_contiguous_slice : std::false_type {
  };
  template <class L, class U>
  struct is_contiguous_slice<contiguous_slice<L, U>> : std::true_type {
  };

  template <class L, class U>
  struct contiguous_normalized_slice;

  template <class T>
  struct is_contiguous_normalized_slice : std::false_type {
  };
  template <class L, class U>
  struct is_contiguous_normalized_slice<contiguous_normalized_slice<L, U>>
      : std::true_type {
  };

  struct normalized_slice {
    long lower, upper, step;
    normalized_slice();
    normalized_slice(long lower, long upper, long step = 1);

    normalized_slice operator*(normalized_slice const &other) const;
    template <class L, class U>
    normalized_slice
    operator*(contiguous_normalized_slice<L, U> const &other) const;
    normalized_slice operator*(slice const &other) const;
    template <class L, class U>
    normalized_slice operator*(contiguous_slice<L, U> const &other) const;

    long size() const;
    inline long get(long i) const;
  };

  struct slice {
    using normalized_type = normalized_slice;

    bound<long> lower, upper, step;
    slice(none<long> lower, none<long> upper, none<long> step);
    slice();

    slice operator*(slice const &other) const;

    template <class L, class U>
    slice operator*(contiguous_slice<L, U> const &other) const;

    /*
       Normalize change a[:-1] to a[:len(a)-1] to have positif index.
       It also check for value bigger than len(a) to fit the size of the
       container
       */
    normalized_slice normalize(long max_size) const;

    /*
     * An assert is raised when we can't compute the size without more
     * informations.
     */
    long size() const;

    long get(long i) const;
  };

  template <class L, class U>
  struct contiguous_normalized_slice {
    long lower;
    long upper;
    static constexpr long step = 1;
    contiguous_normalized_slice();
    contiguous_normalized_slice(long lower, long upper);
    template <class L1, class U1>
    contiguous_normalized_slice(
        contiguous_normalized_slice<L1, U1> const &other)
        : lower(other.lower), upper(other.upper)
    {
    }

    template <class L1, class U1>
    contiguous_normalized_slice<long, long>
    operator*(contiguous_normalized_slice<L1, U1> const &other) const;

    template <class L1, class U1>
    contiguous_normalized_slice<long, long>
    operator*(contiguous_slice<L1, U1> const &other) const;
    normalized_slice operator*(normalized_slice const &other) const;
    normalized_slice operator*(slice const &other) const;

    long size() const;

    inline long get(long i) const;
  };

  template <class L, class U>
  struct contiguous_slice {
    using normalized_type = contiguous_normalized_slice<L, U>;
    L lower;
    U upper;
    static constexpr long step = 1;
    contiguous_slice();
    contiguous_slice(L lower, U upper);
    template <class L1, class U1>
    contiguous_slice(contiguous_slice<L1, U1> const &other);

    template <class L1, class U1>
    contiguous_slice<long, long>
    operator*(contiguous_slice<L1, U1> const &other) const;
    template <class L1, class U1>
    operator contiguous_slice<L1, U1>();

    slice operator*(slice const &other) const;

    /*
       Normalize change a[:-1] to a[:len(a)-1] to have positif index.
       It also check for value bigger than len(a) to fit the size of the
       container
       */
    normalized_type normalize(long max_size) const;

    long size() const;

    inline long get(long i) const;
  };
  template <class L, class U>
  constexpr long contiguous_slice<L, U>::step;

  template <class T>
  struct normalized {
    using type = T;
  };

  template <>
  struct normalized<slice> {
    using type = normalized_slice;
  };

  template <class L, class U>
  struct normalized<contiguous_slice<L, U>> {
    using type = typename contiguous_slice<L, U>::normalized_type;
  };

  template <class S>
  using normalize_t = typename normalized<S>::type;

  template <class S>
  S normalize(S s, long n)
  {
    if (s < 0)
      s += n;
    return s;
  }
  none_type normalize(none_type s, long n)
  {
    return {};
  }
  normalized_slice normalize(slice s, long n)
  {
    return s.normalize(n);
  }
  template <class L, class U>
  typename contiguous_slice<L, U>::normalized_type
  normalize(contiguous_slice<L, U> s, long n)
  {
    return s.normalize(n);
  }

  std::ostream &operator<<(std::ostream &os, slice const &s);
  template <class L, class U>
  std::ostream &operator<<(std::ostream &os, contiguous_slice<L, U> const &s);
}
namespace __builtin__
{
  template <class T>
  auto getattr(types::attr::START, T const &s) -> decltype(s.lower)
  {
    return s.lower;
  }
  template <class T>
  auto getattr(types::attr::STOP, T const &s) -> decltype(s.upper)
  {
    return s.upper;
  }
  template <class T>
  auto getattr(types::attr::STEP, T const &s) -> decltype(s.step)
  {
    return s.step;
  }
  template <class L, class U>
  types::none_type getattr(types::attr::STEP,
                           types::contiguous_slice<L, U> const &s)
  {
    return {};
  }
}
PYTHONIC_NS_END

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <class L1, class U1>
struct __combined<pythonic::types::contiguous_slice<long, long>,
                  pythonic::types::contiguous_slice<U1, L1>> {
  using type = pythonic::types::contiguous_slice<long, long>;
};
template <class L1, class U1>
struct __combined<
    pythonic::types::contiguous_slice<pythonic::types::none_type, long>,
    pythonic::types::contiguous_slice<U1, L1>> {
  using type = pythonic::types::contiguous_slice<U1, long>;
};
template <class L1, class U1>
struct __combined<pythonic::types::contiguous_slice<pythonic::types::none_type,
                                                    pythonic::types::none_type>,
                  pythonic::types::contiguous_slice<U1, L1>> {
  using type = pythonic::types::contiguous_slice<U1, L1>;
};
template <class L1, class U1>
struct __combined<
    pythonic::types::contiguous_slice<long, pythonic::types::none_type>,
    pythonic::types::contiguous_slice<U1, L1>> {
  using type = pythonic::types::contiguous_slice<long, L1>;
};

/* } */

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <class T>
struct to_python<types::bound<T>> {
  static PyObject *convert(types::bound<T> const &n);
};

template <class L, class U>
struct to_python<types::contiguous_slice<L, U>> {
  static PyObject *convert(types::contiguous_slice<L, U> const &n);
};

template <class L, class U>
struct to_python<types::contiguous_normalized_slice<L, U>> {
  static PyObject *convert(types::contiguous_normalized_slice<L, U> const &n);
};

template <>
struct to_python<types::slice> {
  static PyObject *convert(types::slice const &n);
};

template <>
struct to_python<types::normalized_slice> {
  static PyObject *convert(types::normalized_slice const &n);
};

PYTHONIC_NS_END

#endif

#endif
