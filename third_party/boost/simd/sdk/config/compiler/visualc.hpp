//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_COMPILER_VISUALC_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_COMPILER_VISUALC_HPP_INCLUDED

#if !defined(BOOST_SIMD_COMPILER)
  #if defined(BOOST_MSVC)

  //////////////////////////////////////////////////////////////////////////////
  // http://www.boost.org/development/requirements.html#Design_and_Programming
  //////////////////////////////////////////////////////////////////////////////
  #pragma warning( disable : 4554 ) // precedence on & operator
  #pragma warning( disable : 4244 ) // converting types to double
  #pragma warning( disable : 4804 ) // unsafe use of >
  #pragma warning( disable : 4996 ) // unsafe iostream call

  #define BOOST_SIMD_COMPILER_MSVC
  #define BOOST_SIMD_COMPILER BOOST_COMPILER

  #endif
#endif
#endif
