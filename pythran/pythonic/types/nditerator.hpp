#ifndef PYTHONIC_TYPES_NDITERATOR_HPP
#define PYTHONIC_TYPES_NDITERATOR_HPP

#include <iterator>

namespace pythonic {

    namespace types {
        /* Iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct nditerator : public std::iterator<std::random_access_iterator_tag,
                                                     typename std::remove_reference<decltype(std::declval<E&>().fast(0))>::type,
                                                     ptrdiff_t,
                                                     typename std::remove_reference<decltype(std::declval<E&>().fast(0))>::type*,
                                                     typename std::remove_reference<decltype(std::declval<E&>().fast(0))>::type /* no ref here, becasue we return a proxy object */
                                                     >
            {
                E & data;
                long index;
                nditerator(E & data, long index) : data(data), index(index) {}

                auto operator*() -> decltype(data.fast(index)) { return data.fast(index); }
                auto operator*() const -> decltype(data.fast(index)) { return data.fast(index); }
                nditerator<E>& operator++() { ++index; return *this;}
                nditerator<E>& operator--() { --index; return *this;}
                nditerator<E>& operator+=(long i) { index += i; return *this;}
                nditerator<E>& operator-=(long i) { index -= i; return *this;}
                nditerator<E> operator+(long i) const { nditerator<E> other(*this); other += i; return other; }
                nditerator<E> operator-(long i) const { nditerator<E> other(*this); other -= i; return other; }
                long operator-(nditerator<E> const& other) const { return index - other.index; }
                bool operator!=(nditerator<E> const& other) const {
                    return index != other.index;
                }
                bool operator==(nditerator<E> const& other) const {
                    return index == other.index;
                }
                bool operator<(nditerator<E> const& other) const {
                    return index < other.index;
                }
                nditerator& operator=(nditerator const& other) {
                  assert(&data == &other.data);
                  index = other.index;
                  return *this;
                }
            };

        /* Const iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct const_nditerator : public std::iterator<std::random_access_iterator_tag,
                                                           typename std::remove_reference<decltype(std::declval<E&>().fast(0))>::type>
            {
                E const &data;
                long index;
                const_nditerator(E const& data, long index) : data(data), index(index) {
                }

                auto operator*() const -> decltype(data.fast(index)) { return data.fast(index); }
                const_nditerator<E>& operator++() { ++index; return *this;}
                const_nditerator<E>& operator--() { --index; return *this;}
                const_nditerator<E>& operator+=(long i) { index +=  i; return *this;}
                const_nditerator<E>& operator-=(long i) { index -=  i; return *this;}
                const_nditerator<E> operator+(long i) const { const_nditerator<E> other(*this); other += i; return other; }
                const_nditerator<E> operator-(long i) const { const_nditerator<E> other(*this); other -= i; return other; }
                long operator-(const_nditerator<E> const& other) const {
                    return index - other.index;
                }
                bool operator!=(const_nditerator<E> const& other) const {
                    return index != other.index;
                }
                bool operator==(const_nditerator<E> const& other) const {
                    return index == other.index;
                }
                bool operator<(const_nditerator<E> const& other) const {
                    return  index <  other.index;
                }
                const_nditerator& operator=(const_nditerator const& other) { index = other.index; return *this;}
            };

        // build an iterator over T, selecting a raw pointer if possible
        template<bool is_strided>
          struct make_nditerator {
            template<class T>
              auto operator()(T& self, long i) -> decltype(nditerator<T>(self, i)) const {
                return nditerator<T>(self, i);
              }
          };
        template<>
          struct make_nditerator<false> {
            template<class T>
              typename T::dtype * operator()(T& self, long i) const {
                return self.buffer + i;
              }
          };
        template<bool is_strided>
          struct make_const_nditerator {
            template<class T>
              auto operator()(T const& self, long i) -> decltype(const_nditerator<T>(self, i)) const {
                return const_nditerator<T>(self, i);
              }
          };
        template<>
          struct make_const_nditerator<false> {
            template<class T>
              typename T::dtype const* operator()(T const& self, long i) const {
                return self.buffer + i;
              }
          };

    }

}

#endif
