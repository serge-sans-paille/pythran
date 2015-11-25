#ifndef PYTHONIC_OPERATOR_TRUTH_HPP
#define PYTHONIC_OPERATOR_TRUTH_HPP

#include "pythonic/include/operator_/truth.hpp"

#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace operator_
  {
    bool truth(bool const &a)
    {
      return a;
    }

    DEFINE_FUNCTOR(pythonic::operator_, truth);
  }
}

#endif
