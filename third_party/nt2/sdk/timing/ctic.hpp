//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_CTIC_HPP_INCLUDED
#define NT2_SDK_TIMING_CTIC_HPP_INCLUDED

/**
* @file
* @brief Defines and implements the ctic() and ctoc() timing functions.
**/

#include <nt2/sdk/timing/config.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/timing/details/timer.hpp>

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // cycle_based_timer is a timing helper class to be used in the stack counter
  // It use read_cycles() to retrieves cycles based timestamps.
  struct cycle_based_timer
  {
    NT2_SDK_TIMING_DECL static void             Print(const cycles_t& val);
                        static inline cycles_t  Time() { return read_cycles(); }
  };

  // INTERNAL ONLY
  // Static const instance of a cycles_t based counter
  counter<cycles_t,cycle_based_timer>  const cycle_timer = {};
} }

namespace nt2
{
  /**
  * @brief Starts a cycle-based timing section
  *
  * ctic starts a nestable timing section. Timestamp at call point is stored
  * into a stack of timing and pops up at the next call to ctoc()
  *
  * @see toc()
  **/
  inline void ctic()
  {
    details::cycle_timer.tic();
  }

  /**
  * @brief Ends a cycle-based timing section
  *
  * ctoc ends a timing section started by a call to ctic(). Those sections
  * could be nested as long as each toc has a matching ctic().
  *
  * @warning  If ctoc is called without a matching call to ctic(), a runtime
  *           assertion will be triggered.
  *
  * @param display  If true, force the timing result to be displayed on the
  *                 standard output.
  *
  * @return the number of cycles (as a cycles_t) since last call to ctic()
  *
  * @see ctic()
  **/
  inline cycles_t  ctoc( bool display = true )
  {
    return details::cycle_timer.toc(display);
  }
}

#endif
