//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SXFUN_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the sxfun function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for bsxfun functor
     **/
    struct sxfun_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Apply element-by-element operation to n expressions
    with singleton expansion enabled

    sxfun(f,a,b) applies the element-by-element pfo @c f to expressions
    @c a and @c b, with singleton expansion enabled.

    The corresponding dimensions of @c a and @c b must be equal to each other
    or equal to one. Whenever a dimension of @c a or @c b is singleton (i.e equal
    to one), sxfun virtually replicates the array along that dimension to match
    the other array.

    @param a0  Polymorphic Function object to apply
    @param a1 First expression to process
    @param a2  Second expression to process
    @param a3  Third  expression to process
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sxfun_       , sxfun, 4)
  ///@overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sxfun_       , tsxfun, 4)
  ///@overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sxfun_       , bsxfun, 3)
  ///@overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sxfun_       , sxfun, 3)
}

#endif
