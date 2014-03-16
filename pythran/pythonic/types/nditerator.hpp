#ifndef PYTHONIC_TYPES_NDITERATOR_HPP
#define PYTHONIC_TYPES_NDITERATOR_HPP

#include <iterator>

namespace pythonic {

    namespace types {
        /* Iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct nditerator : std::iterator<std::random_access_iterator_tag, typename E::value_type, ptrdiff_t, typename E::value_type *, typename E::value_type /* no ref here, because we *may* be returning a temporary, so there is no point in  taking a reference to the temporary*/> {
                E & data;
                long index;
                nditerator(E & data, long index) : data(data), index(index) {}

                /* we would like to return E::value_type, but this currently fails. So let's the auto magic do the trick */
                auto operator*() -> decltype(data.fast(index)) { return data.fast(index); }
                nditerator<E>& operator++() { index ++; return *this;}
                nditerator<E>& operator--() { index --; return *this;}
                nditerator<E> operator+(long i) const { nditerator<E> other(*this); other.index+=  i; return other; }
                nditerator<E> operator-(long i) const { nditerator<E> other(*this); other.index-=  i; return other; }
                nditerator<E>& operator+=(long i) { index +=  i; return *this;}
                nditerator<E>& operator-=(long i) { index -=  i; return *this;}
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
            };

        /* Const iterator over whatever provides a fast(long) method to access its element
         */
        template<class E>
            struct const_nditerator : std::iterator<std::random_access_iterator_tag, typename E::value_type /* no issue with reference here, as it is a const reference */> {
                E const &data;
                long index;
                const_nditerator(E const& data, long index) : data(data), index(index) {
                }

                auto operator*() const -> decltype(data.fast(index)) { return data.fast(index); }
                const_nditerator<E>& operator++() { index ++ ; return *this;}
                const_nditerator<E>& operator--() { index -- ; return *this;}
                const_nditerator<E> operator+(long i) const { const_nditerator<E> other(*this); other.index +=  i; return other; }
                const_nditerator<E> operator-(long i) const { const_nditerator<E> other(*this); other.index -=  i; return other; }
                const_nditerator<E>& operator+=(long i) { index +=  i; return *this;}
                const_nditerator<E>& operator-=(long i) { index -=  i; return *this;}
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
            };


    }

}

#endif
