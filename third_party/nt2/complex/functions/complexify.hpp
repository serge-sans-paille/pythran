//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_COMPLEXIFY_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_COMPLEXIFY_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the complexify function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the complexify functor
    **/
    struct complexify_ : ext::elementwise_<complexify_>
    {
      typedef ext::elementwise_<complexify_> parent;
    };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::complexify_, complexify, 1)

}

#endif
