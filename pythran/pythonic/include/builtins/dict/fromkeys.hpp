#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_FROMKEYS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_FROMKEYS_HPP

#include "pythonic/include/builtins/None.hpp"
#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/proxy.hpp"

#include <type_traits>

namespace pythonic
{

  namespace builtins
  {

    namespace dict
    {

      template <class Iterable, class V = types::none_type>
      types::dict<typename std::remove_reference<Iterable>::type::value_type, V>
      fromkeys(Iterable &&iter, V const &v = builtins::None);

      PROXY_DECL(pythonic::builtins::dict, fromkeys);
    }
  }
}

#endif
