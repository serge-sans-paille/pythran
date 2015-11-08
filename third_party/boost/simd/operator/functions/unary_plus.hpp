//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief unary_plus generic tag

     Represents the unary_plus function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unary_plus_ : ext::elementwise_<unary_plus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unary_plus_> parent;
    };
  }
  /*!
    return the elementwise unary plus of the parameter
    Infix notation can be used with operator '+'
    This is in fact identity.

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = unary_plus(a0);
    @endcode

    is similar to:

    @code
    T0 r = +a0;
    @endcode

    @par Alias:
    @c identity,  @c id

    @see  @funcref{plus}, @funcref{unary_minus}
    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , unary_plus  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , identity    , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , id          , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::unary_plus>
  {
    typedef boost::simd::tag::unary_plus_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::unary_plus_>
  {
    typedef boost::proto::tag::unary_plus type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
