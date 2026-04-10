#ifndef PYTHONIC_INCLUDE_TYPES_EMPTY_ITERATOR_HPP
#define PYTHONIC_INCLUDE_TYPES_EMPTY_ITERATOR_HPP

#include <iterator>

PYTHONIC_NS_BEGIN

namespace types
{

  struct empty_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type /* no ref */;

    // Empty iterator used, among other things, by empty_set
    empty_iterator() = default;
    empty_iterator(empty_iterator const &) = default;
    bool operator==(empty_iterator const &) const;
    bool operator!=(empty_iterator const &) const;
    bool operator<(empty_iterator const &) const;
    empty_iterator &operator++();
    empty_iterator &operator++(int);
    value_type operator*() const;
    void operator->() const;
  };
} // namespace types
PYTHONIC_NS_END

#endif
