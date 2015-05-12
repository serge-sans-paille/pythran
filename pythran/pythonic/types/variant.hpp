#ifndef PYTHONIC_TYPES_VARIANT_HPP
#define PYTHONIC_TYPES_VARIANT_HPP

#include "pythonic/include/types/variant.hpp"

#include <utility>

namespace pythonic
{

  namespace types
  {

    template <class Type>
    variant<Type>::variant()
        : t(nullptr)
    {
    }

    template <class Type>
    variant<Type>::variant(Type const &t)
        : t(new (mem) Type(t))
    {
    }

    template <class Type>
    variant<Type>::variant(variant<Type> const &t)
        : t(t.t ? new (mem) Type(*t.t) : t.t)
    {
    }

    template <class Type>
    template <class OtherType>
    variant<Type>::variant(variant<OtherType> const &t)
        : t(nullptr)
    {
    }

    template <class Type>
    template <class... Args>
    auto variant<Type>::operator()(Args &&... args)
        -> decltype(std::declval<Type>()(std::forward<Args>(args)...))
    {
      return (*t)(std::forward<Args>(args)...);
    }

    template <class Type, class... Types>
    variant<Type, Types...>::variant()
        : t(nullptr), ot()
    {
    }

    template <class Type, class... Types>
    variant<Type, Types...>::variant(Type const &t)
        : t(new (mem) Type(t)), ot()
    {
    }

    template <class Type, class... Types>
    template <class T>
    variant<Type, Types...>::variant(T const &t)
        : t(nullptr), ot(t)
    {
    }

    // the below constructor handle case when Types and OtherTypes are not
    // exactly the same
    // or are in a different order
    template <class Type, class... Types>
    template <class OtherType, class... OtherTypes>
    variant<Type, Types...>::variant(variant<OtherType, OtherTypes...> const &t)
        : t(nullptr), ot(t.ot)
    {
    }

    template <class Type, class... Types>
    template <class... OtherTypes>
    variant<Type, Types...>::variant(variant<Type, OtherTypes...> const &t)
        : t(t.t ? new (mem) Type(*t.t) : t.t), ot(t.ot)
    {
    }

    template <class Type, class... Types>
    template <class... Args>
    auto variant<Type, Types...>::operator()(Args &&... args)
        -> decltype(std::declval<Type>()(args...))
    {
      if (t)
        return (*t)(args...);
      else
        return ot(args...);
    }
  }
}
#endif
