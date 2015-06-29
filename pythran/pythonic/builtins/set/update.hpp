#ifndef PYTHONIC_SET_UPDATE_HPP
#define PYTHONIC_SET_UPDATE_HPP

#include "pythonic/include/builtins/set/update.hpp"

#include "pythonic/__dispatch__/update.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      ALIAS(update, pythonic::__dispatch__::update);

      PROXY_IMPL(pythonic::builtins::set, update);
    }
  }
}
#endif
