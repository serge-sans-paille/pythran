#ifndef PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_VIEWITEMS_HPP

#include "pythonic/include/__builtin__/dict/viewitems.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      template <class K, class V>
      types::dict_items<types::dict<K, V>> viewitems(types::dict<K, V> const &d)
      {
        return d.viewitems();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::dict, viewitems);
    }
  }
}

#endif
