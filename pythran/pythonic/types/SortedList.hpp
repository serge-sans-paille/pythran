#ifndef PYTHONIC_TYPES_SORTEDLIST_HPP
#define PYTHONIC_TYPES_SORTEDLIST_HPP

#include "pythonic/include/types/SortedList.hpp"

#include "pythonic/builtins/IndexError.hpp"
#include "pythonic/builtins/ValueError.hpp"
#include "pythonic/builtins/len.hpp"
#include "pythonic/types/bool.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/allocate.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/utils/shared_ref.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace types
{

  /// SortedList

  // constructors
  template <class T>
  SortedList<T>::SortedList() : _data(utils::no_memory())
  {
  }
  template <class T>
  template <class InputIterator>
  SortedList<T>::SortedList(InputIterator start, InputIterator stop) : _data(start, stop)
  {
    std::sort(begin(), end());
  }

  // io
  template <class T>
  std::ostream &operator<<(std::ostream &os, SortedList<T> const &v)
  {
    os << "SortedList([";
    auto iter = v.begin();
    if (iter != v.end()) {
      while (iter + 1 != v.end())
        os << *iter++ << ", ";
      os << *iter;
    }
    return os << "])";
  }

  // comparison
  template <class T>
  template <class K>
  bool SortedList<T>::operator==(SortedList<K> const &other) const
  {
    if (size() != other.size())
      return false;
    return std::equal(begin(), end(), other.begin());
  }
  template <class T>
  template <class K>
  bool SortedList<T>::operator!=(SortedList<K> const &other) const
  {
    return !operator==(other);
  }

  // iterators
  template <class T>
  typename SortedList<T>::iterator SortedList<T>::begin()
  {
    return _data->begin();
  }
  template <class T>
  typename SortedList<T>::const_iterator SortedList<T>::begin() const
  {
    return _data->begin();
  }
  template <class T>
  typename SortedList<T>::iterator SortedList<T>::end()
  {
    return _data->end();
  }
  template <class T>
  typename SortedList<T>::const_iterator SortedList<T>::end() const
  {
    return _data->end();
  }
  template <class T>
  typename SortedList<T>::reverse_iterator SortedList<T>::rbegin()
  {
    return _data->rbegin();
  }
  template <class T>
  typename SortedList<T>::const_reverse_iterator SortedList<T>::rbegin() const
  {
    return _data->rbegin();
  }
  template <class T>
  typename SortedList<T>::reverse_iterator SortedList<T>::rend()
  {
    return _data->rend();
  }
  template <class T>
  typename SortedList<T>::const_reverse_iterator SortedList<T>::rend() const
  {
    return _data->rend();
  }

  // comparison
  template <class T>
  bool SortedList<T>::operator<(SortedList<T> const &other) const
  {
    return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
  }
  template <class T>
  bool SortedList<T>::operator>(SortedList<T> const &other) const
  {
    return std::lexicographical_compare(other.begin(), other.end(), begin(), end());
  }
  template <class T>
  bool SortedList<T>::operator<=(SortedList<T> const &other) const
  {
    return !(*this > other);
  }
  template <class T>
  bool SortedList<T>::operator>=(SortedList<T> const &other) const
  {
    return !(*this < other);
  }

  // SortedList interface
  template <class T>
  SortedList<T> SortedList<T>::operator*(long n) const
  {
    auto copy = *this;
    copy *= n;
    return copy;
  }
  template <class T>
  SortedList<T> const &SortedList<T>::operator*=(long n)
  {
    auto &c = *_data;
    if (n == 0) {
      c.clear();
    } else if (n > 1) {
      size_t prev_size = c.size();
      c.resize(prev_size * n);
      auto tail_start = c.end() - prev_size;
      std::move(c.begin(), c.begin() + prev_size, tail_start);
      auto inserter = c.begin();
      while (tail_start != c.end()) {
        std::fill_n(inserter, n, *tail_start);
        inserter += n;
        ++tail_start;
      }
    }
    return *this;
  }
  template <class T>
  template <class E>
  SortedList<T> SortedList<T>::operator+(E &&elt) const
  {
    auto copy = *this;
    copy += std::forward<E>(elt);
    return copy;
  }
  template <class T>
  template <class E>
  SortedList<T> const &SortedList<T>::operator+=(E &&elt)
  {
    auto &c = *_data;
    size_t prev_size = c.size();
    std::sort(elt.begin(), elt.end());
    c.insert(c.end(), elt.begin(), elt.end());
    std::inplace_merge(c.begin(), c.begin() + prev_size, c.end());
    return *this;
  }
  template <class T>
  template <class E>
  void SortedList<T>::add(E &&elt)
  {
    auto &c = *_data;
    auto where = std::lower_bound(c.begin(), c.end(), elt);
    c.insert(where, elt);
  }
  template <class T>
  template <class E>
  long SortedList<T>::count(E &&elt) const
  {
    auto &c = *_data;
    auto where = std::lower_bound(c.begin(), c.end(), elt);
    long count = 0;
    while (where != c.end() && *where == elt) {
      count += 1;
      where += 1;
    }
    return count;
  }
  template <class T>
  template <class E>
  void SortedList<T>::discard(E &&elt)
  {
    auto &c = *_data;
    auto where = std::lower_bound(c.begin(), c.end(), elt);
    if (where != c.end() && *where == elt)
      c.erase(where);
  }
  template <class T>
  template <class E, class StartType, class StopType>
  long SortedList<T>::index(E &&elt, StartType start, StopType stop) const
  {
    const auto &c = *_data;
    const long size = c.size();
    auto istart = c.begin(), istop = c.end();
    if constexpr (!std::is_same<StartType, none_type>::value) {
      if (start < 0)
        start += size;
      istart += start;
      if (istart >= istop)
        throw ValueError(elt);
    }
    if constexpr (!std::is_same<StopType, none_type>::value) {
      if (stop > 0)
        stop = size - stop;
      istop += stop;
      if (istop <= istart)
        throw ValueError(elt);
    }
    auto where = std::lower_bound(istart, istop, elt);
    if (where != c.end() && *where == elt)
      return where - c.begin();
    else
      throw ValueError(elt);
  }
  template <class T>
  T SortedList<T>::pop(long index)
  {
    auto &c = *_data;
    if (index == -1) {
      T val = c.back();
      c.pop_back();
      return val;
    } else {
      if (index < 0)
        index += c.size();
      if (index < 0 || static_cast<size_t>(index) >= c.size())
        throw types::IndexError(index);
      auto where = c.begin() + index;
      T val = *where;
      c.erase(where);
      return val;
    }
  }
  template <class T>
  template <class E>
  void SortedList<T>::remove(E const &elt)
  {
    auto &c = *_data;
    auto where = std::lower_bound(c.begin(), c.end(), elt);
    if (where != c.end() && *where == elt)
      c.erase(where);
    else
      throw types::ValueError(elt);
  }
  template <class T>
  template <class Tp>
  void SortedList<T>::update(SortedList<Tp> const &elt)
  {
    auto &c = *_data;
    size_t prev_size = c.size();
    c.insert(c.end(), elt.begin(), elt.end());
    std::inplace_merge(c.begin(), c.begin() + prev_size, c.end());
  }

  template <class T>
  template <class V>
  bool SortedList<T>::contains(V const &v) const
  {
    auto &c = *_data;
    auto where = std::lower_bound(c.begin(), c.end(), v);
    return where != c.end() && *where == v;
  }

  template <class T>
  intptr_t SortedList<T>::id() const
  {
    return reinterpret_cast<intptr_t>(&(*_data));
  }

  template <class T>
  typename SortedList<T>::const_reference SortedList<T>::fast(long n) const
  {
    assert(n < size());
    return (*_data)[n];
  }
  template <class T>
  typename SortedList<T>::const_reference SortedList<T>::operator[](long n) const
  {
    if (n < 0)
      n += size();
    assert(0 <= n && n < size());
    return fast(n);
  }

  template <class T>
  template <class Sp>
  std::enable_if_t<is_slice<Sp>::value, sliced_list<T, Sp>>
  SortedList<T>::operator[](Sp const &s) const
  {
    return {_data, s.normalize(_data->size())};
  }

  template <class T>
  SortedList<T> SortedList<T>::copy() const
  {
    return {container_type(*_data)};
  }
} // namespace types

PYTHONIC_NS_END

/* overload std::get */
namespace std
{
  template <size_t I, class T>
  typename pythonic::types::SortedList<T>::const_reference
  get(pythonic::types::SortedList<T> const &t)
  {
    return t[I];
  }

} // namespace std
#endif
