//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISDIAGONAL_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISDIAGONAL_HPP_INCLUDED

/*!
  @file
  @brief Defines the isdiagonal function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct isdiagonal_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Test for diagonal status

    Returns @c true iff a0 is a diagonal matrix, which means every elements
    outside its diagonal are equal to 0.

    @param  a0 The expression to test
    @return a boolean value indicating the diagonal status of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, isdiagonal, 1)

  /*!
    @brief Test for diagonal status with precision

    Returns @c true iff a0 is a diagonal matrix up to a given precision, which
    means every elements outside its diagonal are at a distance to 0 of atmost
    a1.

    @param  a0 The expression to test
    @param  a1 Precision treshold to satisfy
    @return a boolean value indicating the  status of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isdiagonal_, isdiagonal, 2)
}

#endif
