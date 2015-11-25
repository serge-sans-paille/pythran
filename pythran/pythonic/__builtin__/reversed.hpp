#ifndef PYTHONIC_BUILTIN_REVERSED_HPP
#define PYTHONIC_BUILTIN_REVERSED_HPP

#include "pythonic/include/__builtin__/reversed.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    namespace details
    {

      template <class Iterable>
      reversed<Iterable>::reversed()
      {
      }

      template <class Iterable>
      reversed<Iterable>::reversed(Iterable const &iterable)
          : iterable(iterable)
      {
      }

      template <class Iterable>
      typename reversed<Iterable>::iterator reversed<Iterable>::begin()
      {
        return iterable.rbegin();
      }

      template <class Iterable>
      typename reversed<Iterable>::iterator reversed<Iterable>::end()
      {
        return iterable.rend();
      }

      template <class Iterable>
      typename reversed<Iterable>::const_iterator
      reversed<Iterable>::begin() const
      {
        return iterable.rbegin();
      }

      template <class Iterable>
      typename reversed<Iterable>::const_iterator
      reversed<Iterable>::end() const
      {
        return iterable.rend();
      }
    }

    template <class Iterable>
    details::reversed<Iterable> reversed(Iterable const &iterable)
    {
      return {iterable};
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, reversed);
  }
}

#endif
