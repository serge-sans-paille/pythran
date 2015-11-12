//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the length function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tag for the length functor
    **/
    struct length_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    Compute largest dimension of an entity.

    @param a0 Expression to compute the length in number of elements
    @return The largest dimension of the size of \c xpr
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::length_, length, 1)
}

#endif
