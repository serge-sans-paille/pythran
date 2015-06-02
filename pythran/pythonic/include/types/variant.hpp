#ifndef PYTHONIC_INCLUDE_TYPES_VARIANT_HPP
#define PYTHONIC_INCLUDE_TYPES_VARIANT_HPP

#include <utility>

namespace pythonic
{

  namespace types
  {
    template <class... Types>
    struct variant;

    template <class Type>
    struct variant<Type> {
      char mem[sizeof(Type)];
      Type *t;

      variant();
      variant(Type const &t);
      variant(variant<Type> const &t);
      template <class OtherType>
      variant(variant<OtherType> const &t);

      template <class... Args>
      auto operator()(Args &&... args)
          -> decltype(std::declval<Type>()(std::forward<Args>(args)...));
    };

    template <class Type, class... Types>
    struct variant<Type, Types...> {
      using callable = void;
      char mem[sizeof(Type)];
      Type *t;
      variant<Types...> ot;

      variant();
      variant(Type const &t);
      template <class T>
      variant(T const &t);

      // the below constructor handle case when Types and OtherTypes are not
      // exactly the same
      // or are in a different order
      template <class OtherType, class... OtherTypes>
      variant(variant<OtherType, OtherTypes...> const &t);

      template <class... OtherTypes>
      variant(variant<Type, OtherTypes...> const &t);

      template <class... Args>
      auto operator()(Args &&... args)
          -> decltype(std::declval<Type>()(args...));
    };
  }
}
#endif
