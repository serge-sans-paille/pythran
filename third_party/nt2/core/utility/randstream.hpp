//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_RANDSTREAM_HPP_INCLUDED
#define NT2_CORE_UTILITY_RANDSTREAM_HPP_INCLUDED

#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/details/rands.hpp>
#include <nt2/core/utility/rng_settings.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/lagged_fibonacci.hpp>

namespace nt2
{
  class randstream_
  {
    public:
    NT2_DEFINE_RANDSTREAM(randstream_);
  };

  extern NT2_CORE_RANDOM_DECL rng_settings current_prng_;
}

#endif

