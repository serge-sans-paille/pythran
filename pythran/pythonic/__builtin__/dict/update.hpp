#ifndef PYTHONIC_BUILTIN_DICT_UPDATE_HPP
#define PYTHONIC_BUILTIN_DICT_UPDATE_HPP

#include "pythonic/include/__builtin__/dict/update.hpp"

#include "pythonic/__dispatch__/update.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace dict
    {

      ALIAS(update, pythonic::__dispatch__::update);

      PROXY_IMPL(pythonic::__builtin__::dict, update);
    }
  }
}

#endif
