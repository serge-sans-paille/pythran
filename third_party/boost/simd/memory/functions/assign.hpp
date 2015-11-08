//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_ASSIGN_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_ASSIGN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief assign generic tag

     Represents the assign function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct assign_ : ext::elementwise_<assign_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<assign_> parent;
    };
  }
  /*!

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = assign(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = ;
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::assign_ , assign , 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::assign_ , set    , 2)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL (tag::assign_ , assign, (A0 const&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL (tag::assign_ , assign, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL (tag::assign_ , assign, (A0&)(A1&), 2)
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::assign>
  {
    typedef boost::simd::tag::assign_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::assign_>
  {
    typedef boost::proto::tag::assign type;
  };
} } }

#include <boost/simd/operator/specific/common.hpp>

#endif
///
