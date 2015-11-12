//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_SECOND_TIMER_HPP_INCLUDED
#define NT2_SDK_TIMING_SECOND_TIMER_HPP_INCLUDED

/**
* @file
* @brief Defines and implements the nt2::time::second_timer scoped timer class.
**/

#include <nt2/sdk/timing/tic.hpp>

namespace nt2 { namespace time
{
  /**
  * @brief Scoped second timer
  *
  * second_timer is a scoped object that performs a timing measurement in seconds
  * in current block. second_timer has to be bound to an external variable
  * that will take care of storing the timing result.
  *
  * @usage
  * @include second_timer.cpp
  *
  * @see nt2::time::cycle_timer
  **/
  struct second_timer
  {
    /**
    * @brief  Initializes a scoped second timer by binding it to an external
    *         timing value and setting up its display policy.
    *
    * @param  elapsed Variable to be updated with the number of seconds measured
    *         by the current timer.
    *
    * @param  display Boolean value that triggers or inhibits the automatic
    *         display of the number of seconds measured by the current timer.
    **/
    second_timer( double& elapsed, bool display = true)
                : elapsed_(elapsed), display_(display)
    {
      tic();
    }

    /**
    * Completes the measure of current block by the scoped second_timer.
    *
    * @post The bound variable contains the number of seconds elapsed in
    *       current scope. If display was set to true, this value is also
    *       printed on the standard output.
    **/
    ~second_timer() { elapsed_ = toc(display_); }

    private:
    double& elapsed_;
    bool    display_;
  };
} }

#endif
