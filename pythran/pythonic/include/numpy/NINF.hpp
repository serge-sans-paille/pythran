#ifndef PYTHONIC_INCLUDE_NUMPY_NINF_HPP
#define PYTHONIC_INCLUDE_NUMPY_NINF_HPP

#include <limits>

namespace pythonic
{

  namespace numpy
  {
    double const NINF = -std::numeric_limits<double>::infinity();
  }
}

#endif
