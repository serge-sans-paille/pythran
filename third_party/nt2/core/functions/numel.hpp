//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NUMEL_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the numel function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tag for the numel functor
    **/
    struct numel_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Number of elements of an expression

    Compute the number of element stored in a given entity.

    @param  a0 Expression to inspect
    @return The number of elements stored in a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::numel_, numel, 1)

  /*!
    @brief

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::numel_, numel, 2)
}

#endif
