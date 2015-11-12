//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_IS_LESS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief is_less generic tag

     Represents the is_less function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_less_ : ext::elementwise_<is_less_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_less_> parent;
    };
  }
  /*!
    Returns True< or False according a0 is less than a1 or not.
   Infix notation can be used with operator '<'.


    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    as_logical<T0> r = is_less(a0,a1);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = a0 < a1;
    @endcode

    @par Alias:
    @c lt, @c is_lt

    @see  @funcref{is_less_equal}, @funcref{is_ltz}, @funcref{is_nge}, @funcref{is_ngez}
    @param a0

    @param a1

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, is_less , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, lt      , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, is_lt   , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::less>
  {
    typedef boost::simd::tag::is_less_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::is_less_>
  {
    typedef boost::proto::tag::less type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
