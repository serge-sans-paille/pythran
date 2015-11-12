//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ARECROSSCOMPATIBLE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ARECROSSCOMPATIBLE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for arecrosscompatible functor
    **/
    struct arecrosscompatible_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Check for cross product compatibility

    For two given expressions and a given dimension, arecrosscompatible verifies
    that both table can be used in a cross product along the chosen dimension.

    @param a0  First expression to cross product
    @param a1  Second expression to cross product
    @param dim Dimension along which the cross product is tested

    @return a boolean value that evaluates to true if @c a0 and @c a1 can be
    used in a cross product along thier @c dim dimension.
  **/
  template< class A0, class A1,class D>
  BOOST_FORCEINLINE
  typename meta::call < tag::arecrosscompatible_( A0 const&, A1 const&
                                                , D const&
                                                )
                      >::type
  arecrosscompatible(A0 const& a0, A1 const& a1, D const& dim)
  {
    return typename make_functor<tag::arecrosscompatible_,A0>::type()(a0,a1,dim);
  }
}

#endif
