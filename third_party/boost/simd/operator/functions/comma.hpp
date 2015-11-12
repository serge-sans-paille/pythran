//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief comma generic tag

     Represents the comma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct comma_ : ext::elementwise_<comma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<comma_> parent;
    };
  }
  /*!
    TODO Put description here

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = comma(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = (a0, a1);
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , comma  , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , then   , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::comma>
  {
    typedef boost::simd::tag::comma_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::comma_>
  {
    typedef boost::proto::tag::comma type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
