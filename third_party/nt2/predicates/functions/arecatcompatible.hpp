//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ARECATCOMPATIBLE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ARECATCOMPATIBLE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for arecatcompatible functor
    **/
    struct arecatcompatible_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Check for concatenation compatibility

    For two given expressions and a given dimension, arecatcompatible verifies
    that the concatenation of both table along the chosen dimension is valid.

    @param a0  First expression to concatenate
    @param a1  Second expression to concatenate
    @param dim Dimension along which the concatenation is tested

    @return a boolean value that evaluates to true if @c a0 and @c a1 can be
    concatenated along thier @c dim dimension.
  **/
  template< class A0, class A1,class D>
  BOOST_FORCEINLINE
  typename meta::call<tag::arecatcompatible_(A0 const&, A1 const&, D const&)>::type
  arecatcompatible(A0 const& a0, A1 const& a1, D const& dim)
  {
    return typename make_functor<tag::arecatcompatible_,A0>::type()(a0,a1,dim);
  }
}

#endif
