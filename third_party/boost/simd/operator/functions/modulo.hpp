//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_MODULO_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_MODULO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief modulo generic tag

     Represents the modulo function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct modulo_ : ext::elementwise_<modulo_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<modulo_> parent;
    };
  }
  /*!
    return the elementwise modulo of the two parameters
    Infix notation can be used with operator '\%'
    Does not work for floating point entries.

    @par Semantic:

    For every parameters of type T0:

    @code
    T0 r = modulo(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0 % a1;
    @endcode

    @see  @funcref{rem}, @funcref{remainder}, @funcref{mod},
    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modulo_             , modulo      , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::modulus>
  {
    typedef boost::simd::tag::modulo_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::modulo_>
  {
    typedef boost::proto::tag::modulus type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
