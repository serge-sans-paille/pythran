#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWVALUES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_VIEWVALUES_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_values<types::dict<K, V>>
      viewvalues(types::dict<K, V> const &d);

      DECLARE_FUNCTOR(pythonic::__builtin__::dict, viewvalues);
    }
  }
}

#endif
