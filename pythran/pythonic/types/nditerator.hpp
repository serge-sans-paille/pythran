#ifndef PYTHONIC_TYPES_NDITERATOR_HPP
#define PYTHONIC_TYPES_NDITERATOR_HPP

#include <iterator>

namespace pythonic {

    namespace types {
        /* Iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct nditerator : public std::iterator<std::random_access_iterator_tag,
                                                     typename E::value_type,
                                                     ptrdiff_t,
                                                     typename E::value_type *, typename E::value_type /* no ref here */> {
                E & data;
                long index;
                nditerator(E & data, long index) : data(data), index(index) {}

                /* we would like to return E::value_type, but this currently fails. So let's the auto magic do the trick */
                auto operator*() -> decltype(data.fast(index)) { return data.fast(index); }
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
                                                           typename E::value_type> {
                E const &data;
                long index;
                const_nditerator(E const& data, long index) : data(data), index(index) {
                }


                // TODO: This "auto" is different than E::value_type, which is weird (if not wrong)
                auto operator*() -> decltype(data.fast(index)) { return data.fast(index); }
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
        /* Const iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct const_ndbiterator : public std::iterator<std::random_access_iterator_tag,
                                                           typename E::value_type> {
                enum mode_t { NO_BROADCAST, BROADCAST_SHAPE0, BROADCAST_SHAPE1};
                E const &data;
                mode_t const mode;
                long index0;
                long index1;
                long shape;
                const_ndbiterator(E const& data, long index, long shape0, long shape1) : data(data), mode(shape0==shape1?NO_BROADCAST : (shape0<shape1?BROADCAST_SHAPE0:BROADCAST_SHAPE1)), index0(mode==BROADCAST_SHAPE0?index%shape0:index), index1(mode==BROADCAST_SHAPE1?index % shape1:index), shape(mode==BROADCAST_SHAPE0?shape0:shape1) {
                }


                // TODO: This "auto" is different than E::value_type, which is weird (if not wrong)
                auto operator*() -> decltype(data.fast(index0, index1)) {
                  return data.fast(index0, index1);
                }

                const_ndbiterator& operator++() {
                  ++index0; ++index1;
                  if(mode == NO_BROADCAST);
                  else if(mode == BROADCAST_SHAPE0) {if(index0==shape) index0=0;}
                  else if(mode == BROADCAST_SHAPE1) {if(index1==shape) index1=0;}
                  return *this;
                }
                const_ndbiterator& operator+=(long i) { index0 +=  i; index1+=i; return *this;}
                const_ndbiterator& operator-=(long i) { index0 -=  i; index1-=i; return *this;}
                const_ndbiterator operator+(long i) const { const_ndbiterator other(*this); other += i; return other; }
                const_ndbiterator operator-(long i) const { const_ndbiterator other(*this); other -= i; return other; }
                long operator-(const_ndbiterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 - other.index0 : index1 - other.index1;
                }
                bool operator!=(const_ndbiterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 != other.index0 : index1 != other.index1;
                }
                bool operator==(const_ndbiterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 == other.index0 : index1 == other.index1;
                }
                bool operator<(const_ndbiterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 < other.index0 : index1 < other.index1;
                }
                const_ndbiterator& operator=(const_ndbiterator const& other) = default;
            };

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
