#ifndef PYTHONIC_INCLUDE_TYPES_EMPTY_ITERATOR_HPP
#define PYTHONIC_INCLUDE_TYPES_EMPTY_ITERATOR_HPP

namespace pythonic
{

  namespace types
  {

    struct empty_iterator : std::iterator<std::forward_iterator_tag, int> {
      // Empty iterator used, among other things, by empty_set
      empty_iterator();
      empty_iterator(empty_iterator const &);
      bool operator==(empty_iterator const &) const;
      bool operator!=(empty_iterator const &) const;
      bool operator<(empty_iterator const &) const;
      empty_iterator &operator++();
      empty_iterator &operator++(int);
      void operator*() const;
      void operator->() const;
    };
  }
}

#endif
