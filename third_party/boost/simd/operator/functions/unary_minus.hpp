//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_UNARY_MINUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief unary_minus generic tag

     Represents the unary_minus function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unary_minus_ : ext::elementwise_<unary_minus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unary_minus_> parent;
    };
  }
  /*!
    return the elementwise unary minus of the parameter
    Infix notation can be used with operator '-'

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = unary_minus(a0);
    @endcode

    is similar to:

    @code
    T0 r = -a0;
    @endcode

    @par Alias:
    @c neg

    @see  @funcref{minus}, @funcref{unary_plus}
    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, unary_minus , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_minus_, neg         , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::negate>
  {
    typedef boost::simd::tag::unary_minus_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::unary_minus_>
  {
    typedef boost::proto::tag::negate type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
