#ifndef PYTHONIC_BUILTIN_ITER_HPP
#define PYTHONIC_BUILTIN_ITER_HPP

#include "pythonic/include/__builtin__/iter.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      /// details iter implementation

      template <class T>
      iter<T>::iter()
      {
      }

      // FIXME : There is a dangling reference as data.begin() is not the one
      // from data "saved" in the "iter" struct
      template <class T>
      iter<T>::iter(T data)
          : iterator(data.begin()), _end(data.end()), data(data)
      {
      }

      template <class T>
      typename iter<T>::iterator &iter<T>::begin()
      {
        return *this;
      }

      template <class T>
      typename iter<T>::iterator const &iter<T>::begin() const
      {
        return *this;
      }

      template <class T>
      typename iter<T>::iterator const &iter<T>::end() const
      {
        return _end;
      }
    }

    /// iter implementation

    template <class T>
    details::iter<
        typename std::remove_cv<typename std::remove_reference<T>::type>::type>
    iter(T &&t)
    {
      return {std::forward<T>(t)};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, iter);
  }
}

#endif
