#ifndef PYTHONIC_TYPES_EMPTY_ITERATOR_HPP
#define PYTHONIC_TYPES_EMPTY_ITERATOR_HPP

#include "pythonic/include/types/empty_iterator.hpp"

namespace pythonic
{

  namespace types
  {

    empty_iterator::empty_iterator()
    {
    }

    empty_iterator::empty_iterator(empty_iterator const &)
    {
    }

    bool empty_iterator::operator==(empty_iterator const &) const
    {
      return true;
    }

    bool empty_iterator::operator!=(empty_iterator const &) const
    {
      return false;
    }

    bool empty_iterator::operator<(empty_iterator const &) const
    {
      return false;
    }

    empty_iterator &empty_iterator::operator++()
    {
      return *this;
    }

    empty_iterator &empty_iterator::operator++(int)
    {
      return *this;
    }

    void empty_iterator::operator*() const
    {
      return;
    }

    void empty_iterator::operator->() const
    {
      return;
    }
  }
}

#endif
