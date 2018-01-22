#ifndef PYTHONIC_INCLUDE_TYPES_ASSIGNABLE_HPP
#define PYTHONIC_INCLUDE_TYPES_ASSIGNABLE_HPP

#include <type_traits>

PYTHONIC_NS_BEGIN

struct dummy {
};

template <class T>
struct assignable {
  using type = T;
};

template <class T>
struct assignable<T const> : assignable<T> {
};

template <class T>
struct assignable<T const &> : assignable<T> {
};

template <class T>
struct assignable<T &> : assignable<T> {
};

template <class T>
struct assignable<T &&> : assignable<T> {
};

template <class T>
struct lazy : assignable<T> {
}; // very conservative

template <class T>
struct returnable : assignable<T> {
};

template <class T>
struct returnable<T const &> : assignable<typename returnable<T>::type> {
};

template <class T>
struct returnable<T &> : assignable<typename returnable<T>::type> {
};

template <class T>
struct returnable<T &&> : assignable<typename returnable<T>::type> {
};
PYTHONIC_NS_END

#endif
