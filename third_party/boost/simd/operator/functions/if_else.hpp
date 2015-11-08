//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief if_else generic tag

     Represents the if_else function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_else_ : ext::elementwise_<if_else_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_else_> parent;
    };
    typedef if_else_ select_;
  }
  /*!
    return the elementwise selected element from the second and third operand
    according to the non nullity of the first operand.
    parameters 2 and 3 must share the same type and also the same element size
    as parameter 1

    @par Semantic:

    For every parameters of types respectively T0, T1, T2:

    @code
    T0 r = if_else(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T0 r = a0 ? a1 : a2;
    @endcode

    @par Alias:
    @c where, @c select,  @c sel


    @see  @funcref{if_else_zero}, @funcref{if_else_allbits}, @funcref{if_zero_else},
    @funcref{if_allbits_else}, @funcref{if_one_else_zero}, @funcref{if_zero_else_one}, @funcref{bitwise_select}
    @param a0

    @param a1

    @param a2

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , if_else         , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , where           , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , select          , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , sel             , 3 )

} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::if_else_>
  {
    typedef boost::simd::tag::if_else_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::if_else_>
  {
    typedef boost::proto::tag::if_else_ type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
