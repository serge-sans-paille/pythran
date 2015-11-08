//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISCOLUMN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISCOLUMN_HPP_INCLUDED

/*!
  @file
  @brief Defines the iscolumn function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for iscolumn functor
    **/
    struct iscolumn_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Test for "column-like" status

    Returns @c true iff the size of a0 is of the form [N 1]

    @param  a0 the first parameter of iscolumn
    @return a boolean value indicating the "column-like" status of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::iscolumn_, iscolumn, 1)
}

#endif
