#ifndef PYTHONIC_INCLUDE_UTILS_ITERATOR_HPP
#define PYTHONIC_INCLUDE_UTILS_ITERATOR_HPP

namespace pythonic
{

  namespace utils
  {

    template <class T>
    struct comparable_iterator : T {
      comparable_iterator();
      comparable_iterator(T const &t);
      bool operator<(comparable_iterator<T> other);
    };

    // Utility class to remind sequence we are iterating on to avoid dangling
    // reference
    template <class T, class... Others>
    struct iterator_reminder {
      std::tuple<T, Others...> value;
      iterator_reminder(T const &v, Others const&... o);
    };

    template <class T>
    struct iterator_reminder<T> {
      T value;
      iterator_reminder(T const &v);
    };
  }
}

#endif
