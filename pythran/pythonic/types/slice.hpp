#ifndef PYTHONIC_TYPES_SLICE_HPP
#define PYTHONIC_TYPES_SLICE_HPP

#include "pythonic/include/types/slice.hpp"
#include "pythonic/types/NoneType.hpp"

#include "pythonic/__builtin__/None.hpp"

#include <cassert>
#include <stdexcept>
#include <ostream>
#include <algorithm>

PYTHONIC_NS_BEGIN

namespace types
{

  namespace details
  {

    long roundup_divide(long a, long b)
    {
      if (b > 0)
        return (a + b - 1) / b;
      else
        return (a + b + 1) / b;
    }
  }

  normalized_slice::normalized_slice()
  {
  }
  normalized_slice::normalized_slice(long lower, long upper, long step)
      : lower(lower), upper(upper), step(step)
  {
  }

  normalized_slice normalized_slice::
  operator*(normalized_slice const &other) const
  {
    return {lower + step * other.lower, lower + step * other.upper,
            step * other.step};
  }
  template <class L, class U>
  normalized_slice normalized_slice::
  operator*(contiguous_normalized_slice<L, U> const &other) const
  {
    return {lower + step * other.lower, lower + step * other.upper,
            step * other.step};
  }
  normalized_slice normalized_slice::operator*(slice const &other) const
  {
    return (*this) * other.normalize(size());
  }

  template <class L, class U>
  normalized_slice normalized_slice::
  operator*(contiguous_slice<L, U> const &other) const
  {
    return (*this) * other.normalize(size());
  }

  long normalized_slice::size() const
  {
    return std::max(0L, details::roundup_divide(upper - lower, step));
  }

  long normalized_slice::get(long i) const
  {
    return lower + i * step;
  }

  slice::slice(none<long> lower, none<long> upper, none<long> step)
      : lower(lower), upper(upper), step(step)
  {
  }

  slice::slice()
      : lower(__builtin__::None), upper(__builtin__::None),
        step(__builtin__::None)
  {
  }

  slice slice::operator*(slice const &other) const
  {
    // We do ! implement these because it requires to know the "end"
    // value of the slice which is ! possible if it is ! "step == 1" slice
    // TODO: We can skip these constraints if we know begin, end && step.
    long sstep = (step.is_none()) ? 1 : (long)step;
    long ostep = (other.step.is_none()) ? 1 : (long)other.step;
    assert(!((ostep < 0 || static_cast<long>(other.upper) < 0 ||
              static_cast<long>(other.lower) < 0) &&
             sstep != 1 && sstep != -1) &&
           "not implemented");
    bound<long> new_lower;
    if (other.lower.is_none() || (long)other.lower == 0) {
      if (ostep > 0)
        new_lower = lower;
      else if (sstep > 0) {
        if (upper.is_none() || (long)upper == 0)
          // 0 means the first value && ! the last value
          new_lower = none_type{};
        else
          new_lower = (long)upper - 1;
      } else {
        if (upper.is_none() || (long)upper == -1)
          new_lower = none_type{};
        else
          new_lower = (long)upper + 1;
      }
    } else {
      none<long> ref = ((long)other.lower > 0) ? lower : upper;
      if (ref.is_none) {
        if (sstep > 0)
          new_lower = (long)other.lower * sstep;
        else
          new_lower = (long)other.lower * sstep - 1;
      } else
        new_lower = (long)ref + (long)other.lower * sstep;
    }

    long new_step = sstep * ostep;

    bound<long> new_upper;
    if (other.upper.is_none()) {
      if (ostep > 0)
        new_upper = upper;
      else if (sstep > 0) {
        if (lower.is_none() || (long)lower == 0)
          new_upper = none_type{};
        else
          new_upper = (long)lower - 1;
      } else {
        if (lower.is_none() || (long)lower == -1)
          // 0 means the first value && ! the last value
          new_upper = none_type{};
        else
          new_upper = (long)lower + 1;
      }
    } else {
      none<long> ref = ((long)other.upper > 0) ? lower : upper;
      if (ref.is_none) {
        if (sstep > 0)
          new_upper = (long)other.upper * sstep;
        else
          new_upper = (long)other.upper * sstep - 1;
      } else
        new_upper = (long)ref + (long)other.upper * sstep;
    }
    return {new_lower, new_upper, new_step};
  }

  /*
     Normalize change a[:-1] to a[:len(a)-1] to have positif index.
     It also check for value bigger than len(a) to fit the size of the
     container
     */
  normalized_slice slice::normalize(long max_size) const
  {
    long sstep = step.is_none() ? 1 : (long)step;
    long normalized_upper;
    if (upper.is_none()) {
      if (sstep > 0L)
        normalized_upper = max_size;
      else
        normalized_upper = -1L;
    } else {
      if (upper < 0L)
        normalized_upper = std::max(-1L, max_size + upper);
      else if (upper > max_size)
        normalized_upper = max_size;
      else
        normalized_upper = (long)upper;
    }

    long normalized_lower;
    if (lower.is_none() && sstep > 0L)
      normalized_lower = 0L;
    else if (lower.is_none() && sstep < 0L)
      normalized_lower = max_size - 1L;
    else if (lower < 0L)
      normalized_lower = std::max(0L, max_size + lower);
    else if (lower > max_size)
      normalized_lower = max_size - 1L;
    else
      normalized_lower = (long)lower;

    return {normalized_lower, normalized_upper, sstep};
  }

  /*
   * An assert is raised when we can't compute the size without more
   * informations.
   */
  long slice::size() const
  {
    long sstep = step.is_none() ? 1 : (long)step;
    assert(!(upper.is_none() && lower.is_none()));
    long len;
    if (upper.is_none()) {
      assert(std::signbit(sstep) != std::signbit((long)lower));
      len = -(long)lower;
    } else if (lower.is_none()) {
      assert(std::signbit(sstep) == std::signbit((long)upper));
      len = upper;
    } else
      len = upper - lower;
    return std::max(0L, details::roundup_divide(len, sstep));
  }

  long slice::get(long i) const
  {
    long sstep = step.is_none() ? 1 : (long)step;
    assert(!upper.is_none() && !lower.is_none());
    return (long)lower + i * sstep;
  }

  template <class L, class U>
  contiguous_normalized_slice<L, U>::contiguous_normalized_slice()
  {
  }

  template <class L, class U>
  contiguous_normalized_slice<L, U>::contiguous_normalized_slice(long lower,
                                                                 long upper)
      : lower(lower), upper(upper)
  {
  }

  template <class L, class U>
  template <class L1, class U1>
  contiguous_normalized_slice<long, long> contiguous_normalized_slice<L, U>::
  operator*(contiguous_normalized_slice<L1, U1> const &other) const
  {
    return {lower + other.lower, lower + other.upper};
  }
  template <class L, class U>
  template <class L1, class U1>
  contiguous_normalized_slice<long, long> contiguous_normalized_slice<L, U>::
  operator*(contiguous_slice<L1, U1> const &other) const
  {
    return (*this) * other.normalize(size());
  }

  template <class L, class U>
  normalized_slice contiguous_normalized_slice<L, U>::
  operator*(normalized_slice const &other) const
  {
    return normalized_slice(lower + step * other.lower,
                            lower + step * other.upper, step * other.step);
  }

  template <class L, class U>
  normalized_slice contiguous_normalized_slice<L, U>::
  operator*(slice const &other) const
  {
    return (*this) * other.normalize(size());
  }

  template <class L, class U>
  long contiguous_normalized_slice<L, U>::size() const
  {
    return std::max(0L, upper - lower);
  }

  template <class L, class U>
  inline long contiguous_normalized_slice<L, U>::get(long i) const
  {
    return lower + i;
  }

  template <class L, class U>
  contiguous_slice<L, U>::contiguous_slice(L lower, U upper)
      : lower(lower), upper(upper)
  {
  }

  long to_lower(long, long v)
  {
    return v;
  }
  long to_lower(long, none_type)
  {
    return 0L;
  }
  none_type to_lower(none_type, none_type)
  {
    return {};
  }

  long to_upper(long, long v)
  {
    return v;
  }
  long to_upper(long, none_type)
  {
    return std::numeric_limits<long>::max();
  }
  none_type to_upper(none_type, none_type)
  {
    return {};
  }

  template <class L, class U>
  template <class L1, class U1>
  contiguous_slice<L, U>::contiguous_slice(
      contiguous_slice<L1, U1> const &other)
      : lower(to_lower(lower, other.lower)), upper(to_upper(upper, other.upper))
  {
  }

  template <class L, class U>
  template <class L1, class U1>
  contiguous_slice<L, U>::operator contiguous_slice<L1, U1>()
  {
    return {to_lower(L1(), lower), to_upper(U1(), upper)};
  }

  template <class L, class U>
  contiguous_slice<L, U>::contiguous_slice()
  {
  }

  template <class L, class U>
  template <class L1, class U1>
  contiguous_slice<long, long> contiguous_slice<L, U>::
  operator*(contiguous_slice<L1, U1> const &other) const
  {
    // FIXME: may need to specialize this one
    long new_lower;
    if (other.lower < 0)
      new_lower = upper + other.lower * step;
    else
      new_lower = lower + other.lower * step;

    bound<long> new_upper;
    if (other.upper.is_none())
      new_upper = upper;
    else if ((long)other.upper < 0) {
      if (upper.is_none())
        new_upper = (long)other.upper * step;
      else
        new_upper = upper + (long)other.upper * step;
    } else
      new_upper = lower + (long)other.upper * step;

    return {new_lower, new_upper};
  }

  template <class L, class U>
  slice contiguous_slice<L, U>::operator*(slice const &other) const
  {
    none<long> new_lower;
    if (other.lower.is_none() || (long)other.lower == 0) {
      if (other.step > 0)
        new_lower = lower;
      else if (upper.is_none() || (long)upper == 0)
        // 0 means the first value && ! the last value
        new_lower = none_type{};
      else
        new_lower = (long)upper - 1;
    } else {
      if ((long)other.lower > 0)
        new_lower = lower + (long)other.lower * step;
      else if (upper.is_none())
        new_lower = (long)other.lower * step;
      else
        new_lower = (long)upper + (long)other.lower * step;
    }

    long new_step = other.step;

    bound<long> new_upper;
    if (other.upper.is_none()) {
      if (other.step > 0)
        new_upper = upper;
      else if ((long)lower == 0)
        new_upper = none_type{};
      else
        new_upper = (long)lower - 1;
    } else {
      if ((long)other.upper > 0)
        new_upper = lower + (long)other.upper * step;
      else if (upper.is_none())
        new_upper = (long)other.upper * step;
      else
        new_upper = (long)upper + (long)other.upper * step;
    }
    return {new_lower, new_upper, new_step};
  }

  /*
     Normalize change a[:-1] to a[:len(a)-1] to have positif index.
     It also check for value bigger than len(a) to fit the size of the
     container
     */
  long upper_size(long upper, long max_size)
  {
    if (upper < 0L)
      return std::max(-1L, max_size + upper);
    else if (upper > max_size)
      return max_size;
    else
      return upper;
  }
  long upper_size(none_type upper, long max_size)
  {
    return max_size;
  }
  long lower_size(long lower, long max_size)
  {
    if (lower < 0L)
      return std::max(0L, max_size + lower);
    else if (lower > max_size)
      return max_size - 1L;
    else
      return lower;
  }
  long lower_size(none_type, long max_size)
  {
    return 0;
  }

  template <class L, class U>
  typename contiguous_slice<L, U>::normalized_type
  contiguous_slice<L, U>::normalize(long max_size) const
  {
    long normalized_upper = upper_size(upper, max_size);
    long normalized_lower = lower_size(lower, max_size);
    return {normalized_lower, normalized_upper};
  }

  template <class L, class U>
  long contiguous_slice<L, U>::size() const
  {
    long len;
    if (upper.is_none()) {
      assert(lower < 0);
      len = -lower;
    } else
      len = upper - lower;
    return std::max(0L, len);
  }

  long get_lower(long l)
  {
    return l;
  }
  long get_lower(none_type)
  {
    return 0;
  }

  template <class L, class U>
  inline long contiguous_slice<L, U>::get(long i) const
  {
    return get_lower(lower) + i;
  }

  template <class L, class U>
  slice slice::operator*(contiguous_slice<L, U> const &other) const
  {
    // We do not implement these because it requires to know the "end"
    // value of the slice which is not possible if it is not "step == 1" slice
    // TODO: We can skip these constraints if we know begin, end && step.
    assert(!((static_cast<long>(other.upper) < 0 ||
              static_cast<long>(other.lower) < 0) &&
             step != 1 && step != -1) &&
           "! implemented");

    bound<long> new_lower;
    if (other.lower == 0)
      new_lower = lower;
    else {
      bound<long> ref = ((long)other.lower > 0) ? lower : upper;
      if (ref.is_none()) {
        if (step > 0)
          new_lower = (long)other.lower * step;
        else
          new_lower = (long)other.lower * step - 1;
      } else
        new_lower = (long)ref + (long)other.lower * step;
    }

    long new_step = step;

    bound<long> new_upper;
    if (other.upper.is_none())
      new_upper = upper;
    else {
      bound<long> ref = ((long)other.upper > 0) ? lower : upper;
      if (ref.is_none()) {
        if (step > 0)
          new_upper = (long)other.upper * step;
        else
          new_upper = (long)other.upper * step - 1;
      } else
        new_upper = (long)ref + (long)other.upper * step;
    }
    return {new_lower, new_upper, new_step};
  }
  template <class T>
  std::ostream &operator<<(std::ostream &os, bound<T> const &b)
  {
    return (b.is_none() ? (os << "None") : (os << (T)b));
  }
  std::ostream &operator<<(std::ostream &os, slice const &s)
  {
    return os << "slice(" << s.lower << ", " << s.upper << ", " << s.step
              << ")";
  }
  template <class L, class U>
  std::ostream &operator<<(std::ostream &os, contiguous_slice<L, U> const &s)
  {
    return os << "slice(" << s.lower << ", " << s.upper << ", " << s.step
              << ")";
  }
}
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE
PYTHONIC_NS_BEGIN

template <class T>
PyObject *to_python<types::bound<T>>::convert(types::bound<T> const &b)
{
  if (b.is_none())
    return ::to_python(types::none_type{});
  else
    return ::to_python((T)b);
}

template <class L, class U>
PyObject *to_python<types::contiguous_normalized_slice<L, U>>::convert(
    types::contiguous_normalized_slice<L, U> const &v)
{
  return PySlice_New(::to_python((long)v.lower), ::to_python((long)v.upper),
                     ::to_python(types::none_type{}));
}

template <class L, class U>
PyObject *to_python<types::contiguous_slice<L, U>>::convert(
    types::contiguous_slice<L, U> const &v)
{
  return PySlice_New(::to_python(v.lower), ::to_python(v.upper),
                     ::to_python(types::none_type{}));
}

PyObject *
to_python<types::normalized_slice>::convert(types::normalized_slice const &v)
{
  if (v.step > 0) {
    return PySlice_New(::to_python(v.lower), ::to_python(v.upper),
                       ::to_python(v.step));
  } else {
    return PySlice_New(::to_python(v.lower),
                       v.upper < 0 ? ::to_python(types::none_type{})
                                   : ::to_python(v.upper),
                       ::to_python(v.step));
  }
}

PyObject *to_python<types::slice>::convert(types::slice const &v)
{
  if (v.step > 0) {
    return PySlice_New(::to_python(v.lower), ::to_python(v.upper),
                       ::to_python(v.step));
  } else {
    return PySlice_New(::to_python(v.lower),
                       v.upper < 0 ? ::to_python(types::none_type{})
                                   : ::to_python(v.upper),
                       ::to_python(v.step));
  }
}
PYTHONIC_NS_END

#endif
#endif
