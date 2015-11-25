#ifndef PYTHONIC_INCLUDE_BUILTIN_ITER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ITER_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class T>
      struct iter : T::iterator {
        using iterator = typename T::iterator;

        iterator _end;
        T data;

        iter();
        iter(T data);
        iterator &begin();
        iterator const &begin() const;
        iterator const &end() const;
      };
    }

    template <class T>
    details::iter<
        typename std::remove_cv<typename std::remove_reference<T>::type>::type>
    iter(T &&t);

    DECLARE_FUNCTOR(pythonic::__builtin__, iter);
  }
}

#endif
