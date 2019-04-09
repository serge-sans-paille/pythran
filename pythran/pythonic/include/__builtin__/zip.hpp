#ifndef PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class... Lists>
  auto zip(Lists &&... lists) -> typename std::enable_if<
      !utils::all_of<(types::len_of<typename std::decay<Lists>::type>::value !=
                      -1)...>::value,
      types::list<decltype(types::make_tuple(*lists.begin()...))>>::type;

  template <class... Tys>
  struct zip_len;
  template <class Ty>
  struct zip_len<Ty> : std::integral_constant<long, types::len_of<Ty>::value> {
  };
  template <class Ty0, class Ty1, class... Tys>
      struct zip_len<Ty0, Ty1, Tys...> : std::integral_constant < long,
      types::len_of<Ty0>::value < zip_len<Ty1, Tys...>::value
          ? types::len_of<Ty0>::value
          : zip_len<Ty1, Tys...>::value > {
  };

  template <class... Lists>
  auto zip(Lists &&... lists) -> typename std::enable_if<
      utils::all_of<(types::len_of<typename std::decay<Lists>::type>::value !=
                     -1)...>::value,
      types::static_list<decltype(types::make_tuple(*lists.begin()...)),
                         zip_len<typename std::decay<Lists>::type...>::value>>::
      type;

  types::empty_list zip();

  DEFINE_FUNCTOR(pythonic::__builtin__, zip);
}
PYTHONIC_NS_END

#endif
