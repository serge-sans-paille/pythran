//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_PLUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_PLUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief plus generic tag

     Represents the plus function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct plus_ : ext::elementwise_<plus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<plus_> parent;
    };
  }
  /*!
    return the elementwise sum of the two parameters
    Infix notation can be used with operator '+'

    @par Semantic:

    For every parameters of type T0:

    @code
    T0 r = plus(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0+a1;
    @endcode

    @par Alias:
    @c add

    @see  @funcref{adds}, @funcref{oneplus}, @funcref{inc}
    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::plus_             , plus            , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::plus_             , add             , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::plus>
  {
    typedef boost::simd::tag::plus_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::plus_>
  {
    typedef boost::proto::tag::plus type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
