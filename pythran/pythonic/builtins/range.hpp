#ifndef PYTHONIC_BUILTIN_RANGE_HPP
#define PYTHONIC_BUILTIN_RANGE_HPP

#include "pythonic/include/builtins/range.hpp"

#include <climits>

#include "pythonic/builtins/range.hpp"
#include "pythonic/types/list.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
  namespace
  {

    long _init_last(long _begin, long _end, long _step)
    {
      if (_step > 0)
        return _begin +
               std::max(0L, _step * ((_end - _begin + _step - 1) / _step));
      else
        return _begin +
               std::min(0L, _step * ((_end - _begin + _step + 1) / _step));
    }
  }

  range_iterator::range_iterator(long v, long s) : value_(v), step_(s)
  {
  }

  long range_iterator::operator*() const
  {
    return value_;
  }

  range_iterator &range_iterator::operator++()
  {
    value_ += step_;
    return *this;
  }

  range_iterator range_iterator::operator++(int)
  {
    range_iterator self(*this);
    value_ += step_;
    return self;
  }

  range_iterator &range_iterator::operator+=(long n)
  {
    value_ += step_ * n;
    return *this;
  }

  range_iterator &range_iterator::operator--()
  {
    value_ -= step_;
    return *this;
  }

  range_iterator range_iterator::operator--(int)
  {
    range_iterator self(*this);
    value_ -= step_;
    return self;
  }

  range_iterator &range_iterator::operator-=(long n)
  {
    value_ -= step_ * n;
    return *this;
  }

  bool range_iterator::operator!=(range_iterator const &other) const
  {
    return value_ != other.value_;
  }

  bool range_iterator::operator==(range_iterator const &other) const
  {
    return value_ == other.value_;
  }

  bool range_iterator::operator<(range_iterator const &other) const
  {
    const long sign = +1 | (step_ >> (sizeof(long) * CHAR_BIT - 1));
    return sign * value_ < sign * other.value_;
  }

  long range_iterator::operator-(range_iterator const &other) const
  {
    return (value_ - other.value_) / step_;
  }

  range::range(long b, long e, long s)
      : begin_(b), end_(_init_last(b, e, s)), step_(s)
  {
  }

  range::range(long e) : begin_(0), end_(e), step_(1)
  {
  }

  range_iterator range::begin() const
  {
    return range_iterator(begin_, step_);
  }

  range_iterator range::end() const
  {
    return range_iterator(end_, step_);
  }

  typename range::reverse_iterator range::rbegin() const
  {
    return {end_ - step_, -step_};
  }

  typename range::reverse_iterator range::rend() const
  {
    return {begin_ - step_, -step_};
  }

  long range::size() const
  {
    return (end_ - begin_) / step_;
  }
  long range::operator[](long i) const
  {
    return begin_ + i * step_;
  }
}
PYTHONIC_NS_END

/* overload std::get */
namespace std
{
  template <size_t I>
  long get(pythonic::builtins::range const &t)
  {
    return t[I];
  }
}

#endif
