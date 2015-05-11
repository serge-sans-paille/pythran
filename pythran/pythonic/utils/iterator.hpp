#ifndef PYTHONIC_UTILS_ITERATOR_HPP
#define PYTHONIC_UTILS_ITERATOR_HPP

#include "pythonic/include/utils/iterator.hpp"

namespace pythonic {

    namespace utils {

        template<class T>
            comparable_iterator<T>::comparable_iterator() :
                T()
            {}

        template<class T>
            comparable_iterator<T>::comparable_iterator(T const & t) :
                T(t)
            {}

        template<class T>
            bool comparable_iterator<T>::operator<(comparable_iterator<T> other)
            {
                return (*this)!= other;
            }
    }

}

#endif
