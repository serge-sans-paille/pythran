#ifndef PYTHONIC_BUILTIN_PYTHRAN_DENONE_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_DENONE_HPP

#include "pythonic/include/__builtin__/pythran/denone.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/NoneType.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace pythran
    {

      types::weak_none_type denone(types::none_type &v)
      {
        return {};
      }
      types::weak_none_type denone(types::none_type const &v)
      {
        return {};
      }
      types::weak_none_type denone(types::none_type &&v)
      {
        return {};
      }

      template <class T>
      T denone(types::none<T> &&v)
      {
        return (T)v;
      }

      template <class T>
      T denone(types::none<T> const &v)
      {
        return (T)v;
      }

      template <class T>
      T denone(types::none<T> &v)
      {
        return (T)v;
      }

      template <class T>
      T denone(T v)
      {
        return v;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::pythran, denone);
    }
  }
}

#endif
