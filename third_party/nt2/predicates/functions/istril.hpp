//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISTRIL_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISTRIL_HPP_INCLUDED

/*!
  @file
  @brief Defines the istril function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for istril functor
    **/
    struct istril_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Is an expression

    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::istril_, istril, 1)
}

#endif
