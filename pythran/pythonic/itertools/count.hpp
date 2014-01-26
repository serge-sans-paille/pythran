#ifndef PYTHONIC_ITERTOOLS_COUNT_HPP
#define PYTHONIC_ITERTOOLS_COUNT_HPP

#include "pythonic/utils/proxy.hpp"
#include <iterator>
#include <limits>

namespace pythonic {

    namespace itertools {
        template<class T>
            struct count_iterator : std::iterator< std::random_access_iterator_tag, T > {
                T value;
                T step;
                count_iterator() {}
                count_iterator(T value, T step) : value(value), step(step) {}
                T operator*() const { return value;}
                count_iterator& operator++() { value+=step; return *this;}
                count_iterator& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(count_iterator const& other) const { return value != other.value; }
                bool operator==(count_iterator const& other) const { return value == other.value; }
                bool operator<(count_iterator const& other) const { return value < other.value; }
                long operator-(count_iterator const& other) const { return (value - other.value)/step; }

            };

        template<class T>
            struct _count :  count_iterator<T> {
                typedef T value_type;
                typedef count_iterator<T> iterator;
                _count() {}
                _count(T value, T step) : count_iterator<T>(value, step) {}
                iterator& begin() { *this; }
                iterator const& begin() const { *this; }
                iterator end() const { return count_iterator<T>(std::numeric_limits<T>::max(), count_iterator<T>::step); }
            };

        template <typename T0, typename T1=T0>
            _count<decltype(std::declval<T0>()+std::declval<T1>())> count(T0 start, T1 step=1) {
                return _count<decltype(std::declval<T0>()+std::declval<T1>())>(start, step);
            }

        _count<long> count() {
            return _count<long>(0, 1);
        }
        PROXY(pythonic::itertools, count);

    }

}

#endif

