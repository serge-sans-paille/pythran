#ifndef PYTHONIC_INCLUDE_TYPES_VARIANT_FUNCTOR_HPP
#define PYTHONIC_INCLUDE_TYPES_VARIANT_FUNCTOR_HPP

#include <utility>
#include "pythonic/include/utils/meta.hpp"

namespace pythonic
{

  namespace types
  {

    /* Variant functor is a generic wrapper for functor object, for which we
     *don't know a priori the common signature,
     * because of of the variadic operator().
     *
     * The trick is to allocate a piece of memory large enough to hold any of
     *the functor, then maintain, for each functor type, a pointer to that type.
     * There can be only one pointer for each variadic set to a non null value
     *(based on the preallocated memory buffer).
     *
     * When calling the functor operator(), the code iterates (linearly) on each
     *pointer and call the operator() of this pointer.
     */

    namespace details
    {

      template <class... Types>
      struct variant_functor_impl;

      template <class Type>
      struct variant_functor_impl<Type> {
        Type *head;

        variant_functor_impl() = default;
        variant_functor_impl(variant_functor_impl const &) = delete;

        variant_functor_impl(char mem[], Type const &t);
        variant_functor_impl(char mem[], variant_functor_impl<Type> const &t);

        template <class... OtherTypes>
        variant_functor_impl(
            char mem[], variant_functor_impl<Type, OtherTypes...> const &t);

        template <class OtherType, class... OtherTypes>
        variant_functor_impl(
            char mem[],
            variant_functor_impl<OtherType, OtherTypes...> const &t);

        template <class OtherType>
        variant_functor_impl(char mem[], OtherType const &t);

        template <class... Args>
        auto operator()(Args &&... args)
            -> decltype(std::declval<Type>()(std::forward<Args>(args)...));

        template <class... Args>
        auto operator()(Args &&... args) const
            -> decltype(std::declval<Type>()(std::forward<Args>(args)...));
      };

      template <class Type, class... Types>
      struct variant_functor_impl<Type, Types...> {

        variant_functor_impl<Type> head;
        variant_functor_impl<Types...> tail;

        variant_functor_impl() = default;
        variant_functor_impl(variant_functor_impl const &) = delete;

        template <class... OtherTypes>
        variant_functor_impl(char mem[], OtherTypes const &... t);

        template <class... OtherTypes>
        variant_functor_impl(char mem[],
                             variant_functor_impl<OtherTypes...> const &t);

        template <class... Args>
        auto operator()(Args &&... args)
            -> decltype(std::declval<Type>()(args...));

        template <class... Args>
        auto operator()(Args &&... args) const
            -> decltype(std::declval<Type>()(args...));
      };
    }

    template <class... Types>
    struct variant_functor : details::variant_functor_impl<Types...> {
      using callable = void;

      // memory used to initialize the actual functor
      // default construction cannot be used because generator are not
      // default-constructible
      char mem[utils::max_element<sizeof(Types)...>::value];

      variant_functor() = default;
      variant_functor(variant_functor const &);

      template <class... OtherTypes>
      variant_functor(OtherTypes const &... t);

      template <class... OtherTypes>
      variant_functor(variant_functor<OtherTypes...> const &t);
    };
  }
}
#endif
