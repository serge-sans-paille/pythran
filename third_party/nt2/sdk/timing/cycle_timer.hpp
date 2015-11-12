//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_CYCLE_TIMER_HPP_INCLUDED
#define NT2_SDK_TIMING_CYCLE_TIMER_HPP_INCLUDED

/**
* @file
* @brief Defines and implements the nt2::time::cycle_timer scoped timer class.
**/

#include <nt2/sdk/timing/ctic.hpp>
#include <nt2/sdk/timing/details/cycles.hpp>

namespace nt2 { namespace time
{
  /**
  * @brief Scoped cycle timer
  *
  * cycle_timer is a scoped object that performs a timing measurement in CPU
  * cycles in current block. cycle_timer has to be bound to an external variable
  * that will take care of storing the timing result.
  *
  * @usage
  * @include cycle_timer.cpp
  *
  * @see nt2::time::second_timer
  **/
  struct cycle_timer
  {
    /**
    * @brief  Initializes a scoped cycle timer by binding it to an external
    *         timing value and setting up its display policy.
    *
    * @param  elapsed Variable to be updated with the number of cycles measured
    *         by the current timer.
    *
    * @param  display Boolean value that triggers or inhibits the automatic
    *         display of the number of cycles measured by the current timer.
    **/
    cycle_timer(nt2::cycles_t& elapsed, bool display = true)
               : elapsed_(elapsed), display_(display)
    {
      ctic();
    }

    /**
    * Completes the measure of current block by the scoped cycle_timer.
    *
    * @post The bound variable contains the number of CPU cycles elapsed in
    *       current scope. If display was set to true, this value is also
    *       printed on the standard output.
    **/
    ~cycle_timer() { elapsed_ = ctoc(display_); }

    private:
    nt2::cycles_t& elapsed_;
    bool display_;
  };
} }

#endif
