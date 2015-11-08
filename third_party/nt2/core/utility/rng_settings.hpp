//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_RNG_SETTINGS_HPP_INCLUDED
#define NT2_CORE_UTILITY_RNG_SETTINGS_HPP_INCLUDED

#include <nt2/core/utility/config.hpp>

namespace nt2
{
  class randstream_;

  struct BOOST_SYMBOL_VISIBLE rng_settings
  {
    NT2_CORE_RANDOM_DECL rng_settings();
    NT2_CORE_RANDOM_DECL rng_settings(rng_settings const&);
    NT2_CORE_RANDOM_DECL rng_settings(randstream_*,int);

    NT2_CORE_RANDOM_DECL rng_settings& operator=(rng_settings const&);

    NT2_CORE_RANDOM_DECL void seed(int );
    NT2_CORE_RANDOM_DECL void generator(randstream_* );

    randstream_*  generator_;
    std::size_t   seed_;
  };
}

#endif
