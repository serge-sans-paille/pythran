//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the linear_interp function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for liner_interp functor
    **/
    struct linear_interp_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    Returns sx-expansion of (1-dx)*a+dx*b
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::linear_interp_, linear_interp, 3)
}

#endif
