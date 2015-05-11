#ifndef PYTHONIC_INCLUDE_UTILS_ITERATOR_HPP
#define PYTHONIC_INCLUDE_UTILS_ITERATOR_HPP

namespace pythonic {

    namespace utils {

        template<class T>
            struct comparable_iterator: T
            {
                comparable_iterator();
                comparable_iterator(T const & t);
                bool operator<(comparable_iterator<T> other);
            };
    }

}

#endif
