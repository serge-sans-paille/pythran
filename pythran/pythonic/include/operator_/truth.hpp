#ifndef PYTHONIC_INCLUDE_OPERATOR_TRUTH_HPP
#define PYTHONIC_INCLUDE_OPERATOR_TRUTH_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    bool truth(bool const &a);

    DECLARE_FUNCTOR(pythonic::operator_, truth);
  }
}

#endif
