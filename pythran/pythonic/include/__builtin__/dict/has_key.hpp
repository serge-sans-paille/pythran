#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_HASKEY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_HASKEY_HPP

#include "pythonic/include/types/dict.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V, class W>
      bool has_key(types::dict<K, V> const &d, W const &k);

      DECLARE_FUNCTOR(pythonic::__builtin__::dict, has_key);
    }
  }
}

#endif
