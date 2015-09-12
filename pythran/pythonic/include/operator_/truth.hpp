#ifndef PYTHONIC_INCLUDE_OPERATOR_TRUTH_HPP
#define PYTHONIC_INCLUDE_OPERATOR_TRUTH_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace operator_
  {
    bool truth(bool const &a);

    PROXY_DECL(pythonic::operator_, truth);
  }
}

#endif
