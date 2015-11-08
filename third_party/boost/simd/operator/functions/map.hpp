//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
   /*!
     @brief map generic tag

     Represents the assign function in generic contexts.

     @par Models:
        Hierarchy
   **/
  namespace tag
  {
    struct map_ : dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef dispatch::tag::formal_ parent;
    };
  }
} }

namespace boost { namespace simd
{
  /*!

    @par Semantic:

    TODO Put description here
    @param a0
    @param a1
    @param a2
    @param a3

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2&)(A3&),4)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&)(A2&)(A3&),4)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&),2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2&),3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&)(A2&),3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,4)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2 const&)(A3&),4)
} }

#endif
