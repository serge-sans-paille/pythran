#ifndef PYTHONIC_UTILS_ITERATOR_HPP
#define PYTHONIC_UTILS_ITERATOR_HPP

namespace pythonic {

    namespace utils {

        template<class T>
            struct comparable_iterator: T {
                comparable_iterator() : T() {}
                comparable_iterator(T const & t) : T(t) {}
                bool operator<(comparable_iterator<T> other) {
                    return (*this)!= other;
                }
            };


    }

}

#endif
