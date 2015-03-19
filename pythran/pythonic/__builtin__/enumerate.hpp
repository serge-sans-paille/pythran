#ifndef PYTHONIC_BUILTIN_ENUMERATE_HPP
#define PYTHONIC_BUILTIN_ENUMERATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/enumerate.hpp"

namespace pythonic {

    namespace __builtin__ {

        /// enumerate_iterator implementation

        template<class Iterator>
            enumerate_iterator<Iterator>::enumerate_iterator()
            {}

        template<class Iterator>
            enumerate_iterator<Iterator>::enumerate_iterator(Iterator const& iter, int first):
                value(first),
                iter(iter)
            {}

        template<class Iterator>
            auto enumerate_iterator<Iterator>::operator*() -> decltype(std::make_tuple(value, *iter))
            {
                return std::make_tuple(value, *iter);
            }

        template<class Iterator>
            typename enumerate_iterator<Iterator>::enumerate_iterator& enumerate_iterator<Iterator>::operator++()
            {
                ++value,++iter;
                return *this;
            }

        template<class Iterator>
            typename enumerate_iterator<Iterator>::enumerate_iterator& enumerate_iterator<Iterator>::operator+=(long n)
            {
                value+=n,iter+=n;
                return *this;
            }

        template<class Iterator>
            bool enumerate_iterator<Iterator>::operator!=(typename enumerate_iterator<Iterator>::enumerate_iterator const& other)
            {
                return iter != other.iter;
            }

        template<class Iterator>
            bool enumerate_iterator<Iterator>::operator<(typename enumerate_iterator<Iterator>::enumerate_iterator const& other)
            {
                return iter < other.iter;
            }

        template<class Iterator>
            long enumerate_iterator<Iterator>::operator-(typename enumerate_iterator<Iterator>::enumerate_iterator const& other)
            {
                return iter - other.iter;
            }

        /// _enumerate implementation

        template <class Iterable>
            _enumerate<Iterable>::_enumerate()
            {}

        template <class Iterable>
             _enumerate<Iterable>::_enumerate(Iterable seq, int first):
                 enumerate_iterator<typename Iterable::iterator>(seq.begin(), first),
                 seq(seq),
                 end_iter(seq.end(), -1)
            {}

        template <class Iterable>
            typename _enumerate<Iterable>::iterator & _enumerate<Iterable>::begin()
            {
                return *this;
            }

        template <class Iterable>
            typename _enumerate<Iterable>::iterator const & _enumerate<Iterable>::begin() const
            {
                return *this;
            }

        template <class Iterable>
            typename _enumerate<Iterable>::iterator _enumerate<Iterable>::end() const
            {
                return end_iter;
            }

        /// enumerate implementation

        template <class Iterable>
            _enumerate<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>
            enumerate(Iterable && seq, long first)
            {
                return _enumerate<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(std::forward<Iterable>(seq), first);
            }

        PROXY_IMPL(pythonic::__builtin__,enumerate);

    }

}

#endif

