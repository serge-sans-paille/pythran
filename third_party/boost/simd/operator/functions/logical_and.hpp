//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_AND_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_AND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief logical_and generic tag

     Represents the logical_and function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_and_ : ext::elementwise_<logical_and_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_and_> parent;
    };
  }
  /*!
    return the logical and of the two parameters
    the operands must of the same type
    Infix notation can be used with operator '&&'

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = logical_and(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = a0 && a1 ;
    @endcode

    @par Alias:
    @c l_and

    @see  @funcref{logical_or}, @funcref{logical_xor}, @funcref{logical_notand},
    @funcref{logical_andnot}, @funcref{logical_notor}, @funcref{logical_ornot}, @funcref{logical_not}
    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_and_      , logical_and     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_and_      , l_and           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::logical_and>
  {
    typedef boost::simd::tag::logical_and_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::logical_and_>
  {
    typedef boost::proto::tag::logical_and type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
