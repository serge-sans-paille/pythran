//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_BITWISE_OR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief bitwise_or generic tag

     Represents the bitwise_or function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct bitwise_or_ : ext::elementwise_<bitwise_or_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitwise_or_> parent;
    };
  }
  /*!
    return the bitwise or of the two parameters
    the operands must share the same bit size and
    the result type is the one of the first operand
    Infix notation can be used with operator '|',
    but this will not work in scalar mode if any
    operand is floating point because of C++ limitations.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = bitwise_or(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0 | a1 ;
    @endcode

    @see  @funcref{bitwise_and}, @funcref{bitwise_xor}, @funcref{bitwise_notand},
    @funcref{bitwise_andnot}, @funcref{bitwise_notor}, @funcref{bitwise_ornot}, @funcref{complement}
    @param a0

    @param a1

    @return a value of the same type as the first parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_or_      , bitwise_or     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_or_      , b_or           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::bitwise_or>
  {
    typedef boost::simd::tag::bitwise_or_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::bitwise_or_>
  {
    typedef boost::proto::tag::bitwise_or type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
