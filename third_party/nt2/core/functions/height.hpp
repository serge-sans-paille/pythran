//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HEIGHT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HEIGHT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the height function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the height functor
    **/
    struct height_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Height of an expression

    Return the number of element stored alogn the height of an expression.

    @param  a0 Expression to compute the size in number of elements
    @return The number of elements stored along the height of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::height_, height, 1)
}

#endif
