//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_TIC_HPP_INCLUDED
#define NT2_SDK_TIMING_TIC_HPP_INCLUDED

/**
* @file
* @brief Defines and implements the tic() and toc() timing functions.
**/

#include <nt2/sdk/timing/config.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/timing/details/timer.hpp>

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // second_based_timer is a timing helper class to be used in the stack counter
  // It use now() to retrieves second based timestamps.
  struct second_based_timer
  {
    NT2_SDK_TIMING_DECL static        void    Print(const double& val);
                        static inline double  Time() { return now(); }
  };

  // INTERNAL ONLY
  // Static const instance of a double based counter
  counter<double,second_based_timer> const sec_timer = {};
} }

namespace nt2
{
  /**
  * @brief Starts a second-based timing section
  *
  * tic starts a nestable timing section. Timestamp at call point is stored
  * into a stack of timing and pops up at the next call to toc()
  *
  * @see toc()
  **/
  inline void tic()
  {
    details::sec_timer.tic();
  }

  /**
  * @brief Ends a second-based timing section
  *
  * toc ends a timing section started by a call to tic(). Those sections
  * could be nested as long as each toc has a matching tic().
  *
  * @warning  If toc is called without a matching call to tic(), a runtime
  *           assertion will be triggered.
  *
  * @param display  If true, force the timing result to be displayed on the
  *                 standard output.
  *
  * @return the number of seconds (as a double) since last call to tic()
  *
  * @see tic()
  **/
  inline double toc( bool display = true )
  {
    return details::sec_timer.toc(display);
  }
}

#endif
