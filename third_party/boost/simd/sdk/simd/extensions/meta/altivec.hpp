
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_ALTIVEC_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_ALTIVEC_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/biggest_integer.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/meta/is_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <climits>

////////////////////////////////////////////////////////////////////////////////
// Altivec PPC extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<> struct is_simd_specific<__vector          float, tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector unsigned int  , tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector unsigned short, tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector unsigned char , tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector signed   int  , tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector signed   short, tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector signed   char , tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector __bool   int  , tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector __bool   short, tag::vmx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__vector __bool   char , tag::vmx_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct as_simd<T, tag::vmx_, typename enable_if_c< is_fundamental<T>::value && !is_same<T, bool>::value >::type>
  {
    template< class Type
            , std::size_t Sz = sizeof(Type)*CHAR_BIT
            , bool Integral = boost::is_integral<T>::value
            , bool Signed = boost::is_signed<T>::value
            , class Dummy=void
            >
    struct entry
    {
      typedef dispatch::meta::na_ type;
    };

    template<bool Sign, class Dummy>
    struct entry<float, 32, false, Sign, Dummy> { typedef __vector float  type;         };
    template<class Type, class Dummy>
    struct entry<Type,  32, true, false, Dummy> { typedef __vector unsigned int   type; };
    template<class Type, class Dummy>
    struct entry<Type,  16, true, false, Dummy> { typedef __vector unsigned short type; };
    template<class Type, class Dummy>
    struct entry<Type,   8, true, false, Dummy> { typedef __vector unsigned char  type; };
    template<class Type, class Dummy>
    struct entry<Type,  32, true, true,  Dummy> { typedef __vector signed int   type;   };
    template<class Type, class Dummy>
    struct entry<Type,  16, true, true,  Dummy> { typedef __vector signed short type;   };
    template<class Type, class Dummy>
    struct entry<Type,   8, true, true,  Dummy> { typedef __vector signed char  type;   };

    typedef typename entry<T>::type type;
  };

  template<class T>
  struct as_simd<logical<T>, tag::vmx_>
  {
    template<class Type, std::size_t Sz = sizeof(Type)*CHAR_BIT, class Dummy = void>
    struct entry
    {
      typedef dispatch::meta::na_ type;
    };

    template<class Type, class Dummy>
    struct entry<Type, 32, Dummy>     { typedef __vector __bool int type;     };
    template<class Type, class Dummy>
    struct entry<Type, 16, Dummy>     { typedef __vector __bool short type;   };
    template<class Type, class Dummy>
    struct entry<Type,  8, Dummy>     { typedef __vector __bool char type;    };

    typedef typename entry<T>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the biggest integer supported by
  // the extension.
  //////////////////////////////////////////////////////////////////////////////
  template<> struct  biggest_integer<tag::vmx_>
  {
    typedef boost::simd::int32_t type;
  };

  template<> struct  biggest_uinteger<tag::vmx_>
  {
    typedef boost::simd::uint32_t type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X>
  struct extension_of<__vector float          ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned int   ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned short ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned char  ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed int     ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed short   ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed char    ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector __bool int     ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector __bool short   ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector __bool char    ,X> { typedef tag::vmx_ type; };

} } }

#endif
