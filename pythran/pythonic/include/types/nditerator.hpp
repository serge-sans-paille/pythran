#ifndef PYTHONIC_INCLUDE_TYPES_NDITERATOR_HPP
#define PYTHONIC_INCLUDE_TYPES_NDITERATOR_HPP

#include <iterator>

namespace pythonic
{

  namespace types
  {
    /* Iterator over whatever provides a fast(long) method to access its element
     */
    template <class E>
    struct nditerator
        : public std::iterator<std::random_access_iterator_tag,
                               typename std::remove_reference<decltype(
                                   std::declval<E &>().fast(0))>::type> {
      E &data;
      long index;
      nditerator(E &data, long index);

      auto operator*() -> decltype(data.fast(index));
      auto operator*() const -> decltype(data.fast(index));
      nditerator<E> &operator++();
      nditerator<E> &operator--();
      nditerator<E> &operator+=(long i);
      nditerator<E> &operator-=(long i);
      nditerator<E> operator+(long i) const;
      nditerator<E> operator-(long i) const;
      long operator-(nditerator<E> const &other) const;
      bool operator!=(nditerator<E> const &other) const;
      bool operator==(nditerator<E> const &other) const;
      bool operator<(nditerator<E> const &other) const;
      nditerator &operator=(nditerator const &other);
    };

    /* Const iterator over whatever provides a fast(long) method to access its
     * element
     */
    template <class E>
    struct const_nditerator
        : public std::iterator<std::random_access_iterator_tag,
                               typename std::remove_reference<decltype(
                                   std::declval<E &>().fast(0))>::type> {
      E const &data;
      long index;
      const_nditerator(E const &data, long index);

      auto operator*() const -> decltype(data.fast(index));
      const_nditerator<E> &operator++();
      const_nditerator<E> &operator--();
      const_nditerator<E> &operator+=(long i);
      const_nditerator<E> &operator-=(long i);
      const_nditerator<E> operator+(long i) const;
      const_nditerator<E> operator-(long i) const;
      long operator-(const_nditerator<E> const &other) const;
      bool operator!=(const_nditerator<E> const &other) const;
      bool operator==(const_nditerator<E> const &other) const;
      bool operator<(const_nditerator<E> const &other) const;
      const_nditerator &operator=(const_nditerator const &other);
    };

    // build an iterator over T, selecting a raw pointer if possible
    template <bool is_strided>
    struct make_nditerator {
      template <class T>
      auto operator()(T &self, long i)
          -> decltype(nditerator<T>(self, i)) const;
    };

    template <>
    struct make_nditerator<false> {
      template <class T>
      typename T::dtype *operator()(T &self, long i) const;
    };

    template <bool is_strided>
    struct make_const_nditerator {
      template <class T>
      auto operator()(T const &self, long i)
          -> decltype(const_nditerator<T>(self, i)) const;
    };

    template <>
    struct make_const_nditerator<false> {
      template <class T>
      typename T::dtype const *operator()(T const &self, long i) const;
    };
  }
}

#endif
