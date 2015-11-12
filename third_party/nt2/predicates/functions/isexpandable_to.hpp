//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISEXPANDABLE_TO_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISEXPANDABLE_TO_HPP_INCLUDED

/*!
  @file
  @brief Define the isexpandable_to function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for isexpandable_to functor
    **/
    struct isexpandable_to_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Check for concatenation compatibility

    For a given expression and a given extent, isexpandable_to verifies
    that the expression can be so expanded.

    @param a0    expression to test
    @param siz   size to test

    @return a boolean value that evaluates to true if @c a0 can be
    expanded_to the size defined in siz.
  **/
  template< class A0, class A1>
  BOOST_FORCEINLINE
  typename meta::call<tag::isexpandable_to_(A0 const&, A1 const&)>::type
  isexpandable_to(A0 const& a0, A1 const& siz)
  {
    return typename make_functor<tag::isexpandable_to_,A0>::type()(a0,siz);
  }
}

#endif
