#ifndef PYTHONIC_TYPES_VARIANT_FUNCTOR_HPP
#define PYTHONIC_TYPES_VARIANT_FUNCTOR_HPP

#include "pythonic/include/types/variant_functor.hpp"

#include <utility>
#include <iostream>

namespace pythonic
{

  namespace types
  {

    namespace details
    {

      template <class Type>
      variant_functor_impl<Type>::variant_functor_impl(char mem[],
                                                       Type const &t)
          : head(new (mem) Type(t))
      {
      }

      template <class Type>
      template <class OtherType>
      variant_functor_impl<Type>::variant_functor_impl(char mem[],
                                                       OtherType const &t)
          : head(nullptr)
      {
      }

      template <class Type>
      variant_functor_impl<Type>::variant_functor_impl(
          char mem[], variant_functor_impl<Type> const &t)
          : head(t.head ? new (mem) Type(*t.head) : nullptr)
      {
      }

      template <class Type>
      template <class... OtherTypes>
      variant_functor_impl<Type>::variant_functor_impl(
          char mem[], variant_functor_impl<Type, OtherTypes...> const &t)
          : variant_functor_impl(mem, t.head)
      {
      }

      template <class Type>
      template <class OtherType, class... OtherTypes>
      variant_functor_impl<Type>::variant_functor_impl(
          char mem[], variant_functor_impl<OtherType, OtherTypes...> const &t)
          : variant_functor_impl(mem, t.tail)
      {
      }

      template <class Type>
      template <class... Args>
      auto variant_functor_impl<Type>::operator()(Args &&... args)
          -> decltype(std::declval<Type>()(std::forward<Args>(args)...))
      {
        return (*head)(std::forward<Args>(args)...);
      }

      template <class Type>
      template <class... Args>
      auto variant_functor_impl<Type>::operator()(Args &&... args) const
          -> decltype(std::declval<Type>()(std::forward<Args>(args)...))
      {
        return (*head)(std::forward<Args>(args)...);
      }

      template <class Type, class... Types>
      template <class... OtherTypes>
      variant_functor_impl<Type, Types...>::variant_functor_impl(
          char mem[], OtherTypes const &... t)
          : head(mem, t...), tail(mem, t...)
      {
      }

      template <class Type, class... Types>
      template <class... OtherTypes>
      variant_functor_impl<Type, Types...>::variant_functor_impl(
          char mem[], variant_functor_impl<OtherTypes...> const &t)
          : head(mem, t), tail(mem, t)
      {
      }

      template <class Type, class... Types>
      template <class... Args>
      auto variant_functor_impl<Type, Types...>::operator()(Args &&... args)
          -> decltype(std::declval<Type>()(args...))
      {
        if (head.head)
          return head(args...);
        else
          return tail(args...);
      }

      template <class Type, class... Types>
      template <class... Args>
      auto variant_functor_impl<Type, Types...>::
      operator()(Args &&... args) const
          -> decltype(std::declval<Type>()(args...))
      {
        if (head.head)
          return head(args...);
        else
          return tail(args...);
      }
    }

    template <class... Types>
    variant_functor<Types...>::variant_functor(variant_functor const &other)
        : details::variant_functor_impl<Types...>(
              mem, static_cast<details::variant_functor_impl<Types...> const &>(
                       other))
    {
    }

    template <class... Types>
    template <class... OtherTypes>
    variant_functor<Types...>::variant_functor(OtherTypes const &... t)
        : details::variant_functor_impl<Types...>(mem, t...)
    {
    }

    template <class... Types>
    template <class... OtherTypes>
    variant_functor<Types...>::variant_functor(
        variant_functor<OtherTypes...> const &t)
        : details::variant_functor_impl<Types...>(
              mem,
              static_cast<details::variant_functor_impl<OtherTypes...> const &>(
                  t))
    {
    }
  }
}
#endif
