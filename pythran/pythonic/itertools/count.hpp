#ifndef PYTHONIC_ITERTOOLS_COUNT_HPP
#define PYTHONIC_ITERTOOLS_COUNT_HPP

#include "pythonic/include/itertools/count.hpp"
#include "pythonic/utils/proxy.hpp"
#include <iterator>
#include <limits>

namespace pythonic {

    namespace itertools {
        template<class T>
            count_iterator<T>::count_iterator()
            {}

        template<class T>
            count_iterator<T>::count_iterator(T value, T step) :
                value(value),
                step(step)
            {}

        template<class T>
            T count_iterator<T>::operator*() const
            {
                return value;
            }

        template<class T>
            count_iterator<T>& count_iterator<T>::operator++()
            {
                value+=step;
                return *this;
            }

        template<class T>
            count_iterator<T>& count_iterator<T>::operator+=(long n)
            {
                value+=step*n;
                return *this;
            }

        template<class T>
            bool count_iterator<T>::operator!=(count_iterator const& other) const
            {
                return value != other.value;
            }

        template<class T>
            bool count_iterator<T>::operator==(count_iterator const& other) const
            {
                return value == other.value;
            }

        template<class T>
            bool count_iterator<T>::operator<(count_iterator const& other) const
            {
                return value < other.value;
            }

        template<class T>
            long count_iterator<T>::operator-(count_iterator const& other) const
            {
                return (value - other.value)/step;
            }

        template<class T>
            _count<T>::_count()
            {}

        template<class T>
            _count<T>::_count(T value, T step) :
                count_iterator<T>(value, step)
            {}

        template<class T>
            typename _count<T>::iterator& _count<T>::begin()
            {
                return *this;
            }

        template<class T>
            typename _count<T>::iterator const& _count<T>::begin() const
            {
                return *this;
            }

        template<class T>
            typename _count<T>::iterator _count<T>::end() const
            {
                return count_iterator<T>(std::numeric_limits<T>::max(), count_iterator<T>::step);
            }

        template <typename T0, typename T1>
            _count<decltype(std::declval<T0>()+std::declval<T1>())> count(T0 start, T1 step)
            {
                return _count<decltype(std::declval<T0>()+std::declval<T1>())>(start, step);
            }

        _count<long> count()
        {
            return _count<long>(0, 1);
        }

        PROXY_IMPL(pythonic::itertools, count);

    }

}

#endif
