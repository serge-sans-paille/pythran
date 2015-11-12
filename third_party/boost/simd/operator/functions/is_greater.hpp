//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief is_greater generic tag

     Represents the is_greater function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_greater_ : ext::elementwise_<is_greater_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_greater_> parent;
    };
  }
  /*!
    Returns True or False according a0 is greater than a1 or not.
    Infix notation can be used with operator '>'.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = is_greater(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = a0 > a1;
    @endcode

    @par Alias:
    @c gt, @c is_gt

    @see  @funcref{is_greater_equal}, @funcref{is_gtz}, @funcref{is_nle}, @funcref{is_nlez}
    @param a0

    @param a1

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, is_greater , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, gt         , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, is_gt      , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::greater>
  {
    typedef boost::simd::tag::is_greater_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::is_greater_>
  {
    typedef boost::proto::tag::greater type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
