//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief divides generic tag

     Represents the divides function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct divides_ : ext::elementwise_<divides_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<divides_> parent;
    };
  }
  /*!
    return the elementwise division of the two parameters
    Infix notation can be used with operator '/'

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = divides(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0/a1;
    @endcode

    @par Alias:
    @c div, @c rdiv

    @see  @funcref{fast_divides}, @funcref{rec}, @funcref{fast_rec}, @funcref{divs}, @funcref{divfloor},
    @funcref{divceil}, @funcref{divround}, @funcref{divround2even}, @funcref{divfix}
    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , divides         , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , div             , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , rdiv            , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::divides>
  {
    typedef boost::simd::tag::divides_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::divides_>
  {
    typedef boost::proto::tag::divides type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
