//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_CENTER_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_CENTER_HPP_INCLUDED

/*!
  @file
  @brief Defines the center function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct center_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief


  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::center_       , center, 3)
}

#endif
