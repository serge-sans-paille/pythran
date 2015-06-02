#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace anonymous
    {
      inline types::empty_set set();

      template <class Iterable>
      inline types::set<
          typename std::remove_reference<Iterable>::type::iterator::value_type>
      set(Iterable &&t);
    }

    PROXY_DECL(pythonic::__builtin__::anonymous, set);
  }
}
#endif
