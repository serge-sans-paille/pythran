#ifndef PYTHONIC_RANDOM_SHUFFLE_HPP
#define PYTHONIC_RANDOM_SHUFFLE_HPP

#include "pythonic/include/random/shuffle.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/random/random.hpp"

#include <limits>

PYTHONIC_NS_BEGIN

namespace random
{

  template <class T>
  types::none_type shuffle(T &seq)
  {
    std::shuffle(seq.begin(), seq.end(), __random_generator);
    return __builtin__::None;
  }

  namespace details
  {
    template <class function>
    struct URG {
      URG(function &&f) : randf(f)
      {
      }

      typedef unsigned result_type;
      result_type min()
      {
        return 0;
      }
      /* -1 because of the floor() operation performed by the float->unsigned
       * conversion */
      result_type max()
      {
        return std::numeric_limits<result_type>::max() - 1;
      }
      result_type operator()()
      {
        return randf() * std::numeric_limits<result_type>::max();
      }

      function randf;
    };
  }

  template <class T, class function>
  types::none_type shuffle(T &seq, function &&randf)
  {
    std::shuffle(seq.begin(), seq.end(),
                 details::URG<function>(std::forward<function>(randf)));
    return __builtin__::None;
  }

  DEFINE_FUNCTOR(pythonic::random, shuffle)
}

PYTHONIC_NS_END

#endif
