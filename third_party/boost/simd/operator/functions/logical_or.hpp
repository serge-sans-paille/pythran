//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_OR_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_LOGICAL_OR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief logical_or generic tag

     Represents the logical_or function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_or_ : ext::elementwise_<logical_or_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_or_> parent;
    };
  }
  /*!
    return the logical or of the two parameters
    the operands must of the same type
    Infix notation can be used with operator '||'

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = logical_or(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = a0 || a1;
    @endcode

    @par Alias:
    @c l_or

    @see  @funcref{logical_and}, @funcref{logical_xor}, @funcref{logical_notand},
    @funcref{logical_andnot}, @funcref{logical_notor}, @funcref{logical_ornot}, @funcref{logical_not}
    @param a0

    @param a1

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_or_      , logical_or     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_or_      , l_or           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::logical_or>
  {
    typedef boost::simd::tag::logical_or_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::logical_or_>
  {
    typedef boost::proto::tag::logical_or type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
