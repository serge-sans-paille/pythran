
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/biggest_integer.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

////////////////////////////////////////////////////////////////////////////////
// SSE extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<> struct is_simd_specific<__m128 , tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128d, tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128i, tag::sse_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct as_simd<float, tag::sse_>
  {
    typedef __m128 type;
  };

  template<>
  struct as_simd<double, tag::sse_>
  {
    typedef __m128d type;
  };

  template<class T>
  struct as_simd<T, tag::sse_, typename enable_if_c< is_integral<T>::value && !is_same<T, bool>::value >::type>
  {
    typedef __m128i type;
  };

  template<class T>
  struct as_simd<logical<T>, tag::sse_>
    : as_simd<T, tag::sse_>
  {
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m128 ,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128d,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128i,X>  { typedef tag::sse_ type; };

} } }

#endif
