#ifndef PYTHONIC_BUILTIN_DICT_HASKEY_HPP
#define PYTHONIC_BUILTIN_DICT_HASKEY_HPP

#include "pythonic/include/__builtin__/dict/has_key.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {
      template <class K, class V, class W>
      bool has_key(types::dict<K, V> const &d, W const &k)
      {
        return d.find(k) != d.item_end();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, has_key);
    }
  }
}

#endif
