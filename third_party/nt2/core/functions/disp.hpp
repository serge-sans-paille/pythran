//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the disp function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the disp functor
    **/
    struct disp_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Display text or expressions

    @c disp(a0) displays the content of @c a0 in a way similar to MATLAB.

    @param a0 Value to display
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::disp_,disp,1)
}

#endif
