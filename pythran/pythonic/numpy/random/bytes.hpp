#ifndef PYTHONIC_NUMPY_RANDOM_BYTES_HPP
#define PYTHONIC_NUMPY_RANDOM_BYTES_HPP

#include "pythonic/include/numpy/random/bytes.hpp"
#include "pythonic/include/numpy/random/generator.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <random>
#include <string>

namespace pythonic
{
  namespace numpy
  {
    namespace random
    {

      types::str bytes(long length)
      {
        // dummy init + rewrite is faster than reserve and push_back
        types::str result(std::string(length, 0));
        std::uniform_int_distribution<long> distribution{0, 255};
        std::generate(result.begin(), result.end(), [&]() {
          return static_cast<char>(distribution(details::generator));
        });
        return result;
      }

      DEFINE_FUNCTOR(pythonic::numpy::random, bytes);
    }
  }
}

#endif
