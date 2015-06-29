#ifndef PYTHONIC_BUILTIN_PYTHRAN_LEN_SET_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_LEN_SET_HPP

#include "pythonic/include/builtins/pythran/len_set.hpp"

#include "pythonic/utils/proxy.hpp"

#include <set>

namespace pythonic
{

  namespace builtins
  {

    namespace pythran
    {

      template <class Iterable>
      long len_set(Iterable const &s)
      {
        return std::set<typename Iterable::iterator::value_type>(
                   s.begin(), s.end()).size();
      }

      PROXY_IMPL(pythonic::builtins::pythran, len_set);
    }
  }
}

#endif
