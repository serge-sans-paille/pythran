#ifndef PYTHONIC_INCLUDE_TYPES_SORTEDLIST_HPP
#define PYTHONIC_INCLUDE_TYPES_SORTEDLIST_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/empty_iterator.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/types/slice.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/types/vectorizable_type.hpp"
#include "pythonic/include/utils/allocate.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/utils/reserve.hpp"
#include "pythonic/include/utils/shared_ref.hpp"

#include <algorithm>
#include <ostream>
#include <utility>
#include <vector>

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  using SortedList_container = std::vector<T, utils::allocator<T>>;

  /* forward declaration */
  template <class T>
  class SortedList;

  /* SortedList */
  template <class T>
  class SortedList
  {
    static constexpr size_t DEFAULT_CAPACITY = 16;

    // data holder
    using _type = std::remove_cv_t<std::remove_reference_t<T>>;
    using container_type = SortedList_container<_type>;

    SortedList(container_type &&c) : _data(std::move(c))
    {
    }

  public:
    utils::shared_ref<container_type> _data;

  public:
    // types
    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    using allocator_type = typename container_type::allocator_type;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;

    // constructors
    SortedList();
    template <class InputIterator>
    SortedList(InputIterator start, InputIterator stop);

    template <class Tp, size_t N>
    SortedList(static_list<Tp, N> const &other) : SortedList(other.begin(), other.end())
    {
    }

    // io
    template <class S>
    friend std::ostream &operator<<(std::ostream &os, SortedList<S> const &v);

    // comparison
    template <class K>
    bool operator==(SortedList<K> const &other) const;
    template <class K>
    bool operator!=(SortedList<K> const &other) const;

    // iterators
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    // accessors
    const_reference operator[](long n) const;
    const_reference fast(long n) const;
    template <class Sp>
    std::enable_if_t<is_slice<Sp>::value, sliced_list<T, Sp>> operator[](Sp const &s) const;

    // comparison
    bool operator<(SortedList<T> const &other) const;
    bool operator<=(SortedList<T> const &other) const;
    bool operator>(SortedList<T> const &other) const;
    bool operator>=(SortedList<T> const &other) const;

    // SortedList interface
    SortedList<T> operator*(long t) const;
    SortedList<T> const &operator*=(long t);
    template <class E>
    SortedList<T> operator+(E &&elt) const;
    template <class E>
    SortedList<T> const &operator+=(E &&elt);
    template <class E>
    void add(E &&elt);
    void clear()
    {
      _data->clear();
    }
    template <class E>
    long count(E &&elt) const;
    template <class E>
    void discard(E &&elt);
    template <class E, class StartType = none_type, class StopType = none_type>
    long index(E &&elt, StartType start = {}, StopType stop = {}) const;
    T pop(long index = -1);
    template <class E>
    void remove(E const &elt);
    template <class E>
    void update(E &&elts)
    {
      (*this) += std::forward<E>(elts);
    }
    template <class Tp>
    void update(SortedList<Tp> const &elts);
    long size() const
    {
      return _data->size();
    }
    template <class V>
    bool contains(V const &v) const;
    intptr_t id() const;

    SortedList<T> copy() const;
  };

} // namespace types

PYTHONIC_NS_END

/* overload std::get */
namespace std
{
  template <size_t I, class T>
  typename pythonic::types::SortedList<T>::const_reference
  get(pythonic::types::SortedList<T> const &t);

  template <size_t I, class T>
  struct tuple_element<I, pythonic::types::SortedList<T>> {
    using type = typename pythonic::types::SortedList<T>::value_type;
  };
} // namespace std

#endif
