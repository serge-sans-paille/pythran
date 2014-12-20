#ifndef PYTHRAN_YIELD_HPP
#define PYTHRAN_YIELD_HPP

/*
 * This contains base class for yielders
 */

#include "pythonic/types/generator.hpp"

namespace pythonic {
  class yielder
  {
    public:
      yielder() : __generator_state(0) {}

      bool operator!=(yielder const & other) const
      {
        return __generator_state != other.__generator_state;
      }
      bool operator==(yielder const & other) const
      {
        return __generator_state == other.__generator_state;
      }

      long __generator_state;
  };

}

#endif
