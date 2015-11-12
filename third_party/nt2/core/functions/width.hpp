//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WIDTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WIDTH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::width function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct width_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Compute the width of a given entity in number of elements
   *
   * \param a0 Expression to inspect
   * \return The width of \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::width_, width, 1)
}

#endif
