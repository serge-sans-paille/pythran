#ifndef PYTHONIC_INCLUDE_BUILTIN_ENUMERATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ENUMERATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"

#include <iterator>

namespace pythonic {

    namespace __builtin__ {

        template<class Iterator>
            struct enumerate_iterator : public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
                                                             std::tuple<long, typename std::iterator_traits<Iterator>::value_type>,
                                                             ptrdiff_t,
                                                             std::tuple<long, typename std::iterator_traits<Iterator>::value_type>*,
                                                             std::tuple<long, typename std::iterator_traits<Iterator>::value_type> /* not a ref */
                                                             >
            {
                long value;
                Iterator iter;
                enumerate_iterator();
                enumerate_iterator(Iterator const& iter, int first);
                auto operator*() -> decltype(std::make_tuple(value, *iter));
                enumerate_iterator& operator++();
                enumerate_iterator& operator+=(long n);
                bool operator!=(enumerate_iterator const& other);
                bool operator<(enumerate_iterator const& other);
                long operator-(enumerate_iterator const& other);
            };

        template <class Iterable>
            struct _enumerate : enumerate_iterator<typename Iterable::iterator>
            {
                using iterator = enumerate_iterator<typename Iterable::iterator>;
                Iterable seq; // we need to keep one ref over the enumerated sequence alive
                iterator end_iter;

                _enumerate();
                _enumerate( Iterable seq, int first );
                iterator & begin();
                iterator const & begin() const;
                iterator end() const;
            };

        template <class Iterable>
            _enumerate<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>
            enumerate(Iterable && seq, long first=0L);

        PROXY_DECL(pythonic::__builtin__,enumerate);

    }

}

#endif
