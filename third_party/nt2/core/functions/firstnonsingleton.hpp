//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIRSTNONSINGLETON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIRSTNONSINGLETON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the nt2::firstnonsingleton function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for firstnonsingleton functor
    **/
    struct firstnonsingleton_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief First non-singleton dimension

    For a given expression, returns the first dimension which is not equal to 1.

    @param a0 Expression to inspect
    @return The value of the first dimension of a0 not equal to 1.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::firstnonsingleton_,firstnonsingleton,1)
}

#endif
