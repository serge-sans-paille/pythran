#ifndef PYTHONIC_TYPES_EMPTY_ITERATOR_HPP
#define PYTHONIC_TYPES_EMPTY_ITERATOR_HPP

#include "pythonic/include/types/empty_iterator.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  inline bool empty_iterator::operator==(empty_iterator const &) const
  {
    return true;
  }

  inline bool empty_iterator::operator!=(empty_iterator const &) const
  {
    return false;
  }

  inline bool empty_iterator::operator<(empty_iterator const &) const
  {
    return false;
  }

  inline empty_iterator &empty_iterator::operator++()
  {
    return *this;
  }

  inline empty_iterator &empty_iterator::operator++(int)
  {
    return *this;
  }

  inline typename empty_iterator::value_type empty_iterator::operator*() const
  {
    return {};
  }

  inline void empty_iterator::operator->() const
  {
  }
} // namespace types
PYTHONIC_NS_END

#endif
