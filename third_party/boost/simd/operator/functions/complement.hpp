//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief complement generic tag

     Represents the complement function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct complement_ : ext::elementwise_<complement_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<complement_> parent;
    };
  }
  /*!
    return the bitwise complement of the entry
    Infix notation can be used with operator '~'

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = complement(a0);
    @endcode

    is similar to:

    @code
    T0 r = ~a0;
    @endcode

    @par Alias:
    @c b_not, @c bitwise_not

    @see  @funcref{bitwise_and}, @funcref{bitwise_or}, @funcref{bitwise_xor}, @funcref{bitwise_notand},
    @funcref{bitwise_andnot}, @funcref{bitwise_notor}, @funcref{bitwise_ornot}
    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , complement  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , bitwise_not , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , b_not       , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::complement>
  {
    typedef boost::simd::tag::complement_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::complement_>
  {
    typedef boost::proto::tag::complement type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
