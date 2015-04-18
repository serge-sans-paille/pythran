#ifndef PYTHONIC_INCLUDE_ITERTOOLS_COUNT_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_COUNT_HPP

#include "pythonic/utils/proxy.hpp"
#include <iterator>
#include <limits>

namespace pythonic {

    namespace itertools {
        template<class T>
            struct count_iterator : std::iterator< std::random_access_iterator_tag, T >
            {
                T value;
                T step;
                count_iterator();
                count_iterator(T value, T step);
                T operator*() const;
                count_iterator& operator++();
                count_iterator& operator+=(long n);
                bool operator!=(count_iterator const& other) const;
                bool operator==(count_iterator const& other) const;
                bool operator<(count_iterator const& other) const;
                long operator-(count_iterator const& other) const;
            };

        template<class T>
            struct _count :  count_iterator<T>
            {
                using value_type = T;
                using iterator = count_iterator<T>;
                _count();
                _count(T value, T step);
                iterator& begin();
                iterator const& begin() const;
                iterator end() const;
            };

        template <typename T0, typename T1=T0>
            _count<decltype(std::declval<T0>()+std::declval<T1>())>
            count(T0 start, T1 step=1);

        _count<long> count();

        PROXY_DECL(pythonic::itertools, count);

    }

}

#endif
