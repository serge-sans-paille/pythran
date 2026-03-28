#ifndef PYTHONIC_INCLUDE_TYPES_GENERATOR_HPP
#define PYTHONIC_INCLUDE_TYPES_GENERATOR_HPP

#include <cstddef>
#include <iterator>

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  struct generator_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename T::result_type;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type /* no ref */;

    T the_generator;
    generator_iterator();
    generator_iterator(T const &a_generator);
    generator_iterator &operator++();
    value_type operator*() const;
    bool operator!=(generator_iterator<T> const &other) const;
    bool operator==(generator_iterator<T> const &other) const;
    bool operator<(generator_iterator<T> const &other) const;
  };
} // namespace types
PYTHONIC_NS_END

#endif
