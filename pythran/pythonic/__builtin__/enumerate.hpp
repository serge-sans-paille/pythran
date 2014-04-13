#ifndef PYTHONIC_BUILTIN_ENUMERATE_HPP
#define PYTHONIC_BUILTIN_ENUMERATE_HPP

#include "pythonic/utils/proxy.hpp"

#include <iterator>

namespace pythonic {

    namespace __builtin__ {
        template<class Iterator>
            struct enumerate_iterator : public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
            std::tuple<long, typename std::iterator_traits<Iterator>::value_type>,
            ptrdiff_t,
            std::tuple<long, typename std::iterator_traits<Iterator>::value_type>*,
            std::tuple<long, typename std::iterator_traits<Iterator>::value_type> /* not a ref */
                                        >{
                                            long value;
                                            Iterator iter;
                                            enumerate_iterator(){}
                                            enumerate_iterator(Iterator const& iter, int first) : value(first), iter(iter) {}
                                            auto operator*() -> decltype(std::make_tuple(value, *iter)) { return std::make_tuple(value, *iter); }
                                            enumerate_iterator& operator++() { ++value,++iter; return *this; }
                                            enumerate_iterator& operator+=(long n) { value+=n,iter+=n; return *this; }
                                            bool operator!=(enumerate_iterator const& other) { return iter != other.iter; }
                                            bool operator<(enumerate_iterator const& other) { return iter < other.iter; }
                                            long operator-(enumerate_iterator const& other) { return iter - other.iter; }
                                        };

        template <class Iterable>
            struct _enumerate : enumerate_iterator<typename Iterable::iterator> {
                typedef enumerate_iterator<typename Iterable::iterator> iterator;
                Iterable seq; // we need to keep one ref over the enumerated sequence alive
                iterator end_iter;

                _enumerate() {}
                _enumerate( Iterable seq, int first ) :  enumerate_iterator<typename Iterable::iterator>(seq.begin(), first), seq(seq), end_iter(seq.end(), -1) {}
                iterator & begin() { return *this; }
                iterator const & begin() const { return *this; }
                iterator end() const { return end_iter; }
            };

        template <class Iterable>
            _enumerate<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> enumerate(Iterable && seq, long first = 0L) {
                return _enumerate<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(std::forward<Iterable>(seq), first);
            }

        PROXY(pythonic::__builtin__,enumerate);

    }

}

#endif

