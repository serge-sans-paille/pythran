//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RNG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RNG_HPP_INCLUDED

#include <nt2/core/utility/randstream.hpp>
#include <nt2/sdk/timing/now.hpp>

namespace nt2
{
  namespace details
  {
    struct shuffle_t  {};
    struct default_t  {};
  }

  details::shuffle_t const shuffle_ = {};
  details::default_t const default_ = {};

  /*!
    @brief PRNG control access

    Return the current PRNG settings object

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng()
  {
    return current_prng_;
  }

  /*!
    @brief PRNG seeding

    Set the seed of the current PRNG.

    @param seed Seed of the PRNG

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(int seed)
  {
    current_prng_.seed(seed);
    return current_prng_;
  }

  /*!
    @brief Time based PRNG seeding

    Set the seed of the current PRNG using current time.

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(details::shuffle_t const&)
  {
    current_prng_.seed( (int)(time_quantum()) );
    return current_prng_;
  }

  /*!
    @brief PRNG reset

    Reset the PRNG settings to the initial state

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(details::default_t const&)
  {
    rng_settings that;
    current_prng_ = that;
    return current_prng_;
  }

  /*!
    @brief PRNG setup

    Set the current PRNG to be equal to another PRNG settings

    @param prng PRNG settings object

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(rng_settings const& prng)
  {
    current_prng_ = prng;
    return current_prng_;
  }

  /*!
    @brief PRNG setup

    Set the current PRNG usign a seed and a generator.

    @param seed PRNG seed
    @param gen  PRNG generator

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(int seed, randstream_* gen)
  {
    return rng( rng_settings(gen,seed) );
  }

  /*!
    @brief PRNG setup

    Set the current PRNG using time as a seed and a generator.

    @param g  PRNG generator

    @return A reference to the current PRNG settings object
  **/
  BOOST_FORCEINLINE rng_settings rng(details::shuffle_t const&, randstream_* g)
  {
    return rng( rng_settings(g,(int)(time_quantum())) );
  }
}

#endif
