//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_MULTIPLIES_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief multiplies generic tag

     Represents the multiplies function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct multiplies_ : ext::elementwise_<multiplies_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<multiplies_> parent;
    };
  }
  /*!
    return the elementwise multiplication of the two parameters
    Infix notation can be used with operator '*'

    @par Semantic:

    For every parameters of type T0:

    @code
    T0 r = multiplies(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0*a1;
    @endcode

    @par Alias:
    @c mul, @c times

    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::multiplies_             , multiplies      , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::multiplies_             , mul             , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::multiplies_             , times           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::multiplies>
  {
    typedef boost::simd::tag::multiplies_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::multiplies_>
  {
    typedef boost::proto::tag::multiplies type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
