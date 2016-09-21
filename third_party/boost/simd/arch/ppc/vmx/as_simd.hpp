//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_AS_SIMD_HPP_INCLUDED

#include <boost/simd/arch/common/simd/as_simd.hpp>
#include <boost/simd/arch/ppc/tags.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch/meta/is_natural.hpp>
#include <boost/simd/detail/dispatch/meta/sign_of.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  namespace ext
  {
    template<> struct as_simd<float, boost::simd::vmx_>
    {
      using type = __vector float;
    };

    template<typename T>
    struct as_simd<logical<T>, boost::simd::vmx_>
    {
      template<std::size_t C> struct key_ {};
      using t2b = brigand::map< brigand::pair<key_<1>,__vector __bool char  >
                              , brigand::pair<key_<2>,__vector __bool short >
                              , brigand::pair<key_<4>,__vector __bool int   >
                              >;

      using type = brigand::at<t2b, key_<sizeof(T)>>;
    };

    template<typename T>
    struct as_simd< T, boost::simd::vmx_
                  , typename std::enable_if<boost::dispatch::is_natural<T>::value>::type
                  >
    {
      template<std::size_t C, typename S> struct key_ {};

      using t2b = brigand::map< brigand::pair < key_<1,signed>  , __vector signed char    >
                              , brigand::pair < key_<1,unsigned>, __vector unsigned char  >
                              , brigand::pair < key_<2,signed>  , __vector signed short   >
                              , brigand::pair < key_<2,unsigned>, __vector unsigned short >
                              , brigand::pair < key_<4,signed>  , __vector signed int     >
                              , brigand::pair < key_<4,unsigned>, __vector unsigned int   >
                              >;

      using type = brigand::at< t2b
                              , key_<sizeof(T),boost::dispatch::sign_of_t<T>>
                              >;
   };
  }
} }

#endif
