//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_SIZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::relative_size function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct relative_size_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Computes parts if the size to be used in indexed access computation
   *
   * \param a0 xpr   Indexing expression
   * \param a1 szs   Indexed node Size
   * \param a2 bis   Indexed node base indices
   * \return The number of elements dimensions required to store \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::relative_size_, relative_size, 3)
}

#endif
