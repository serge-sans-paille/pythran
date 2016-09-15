//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_PACK_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_PACK_TRAITS_HPP_INCLUDED

#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/pack_traits.hpp>
#include <boost/simd/arch/common/simd/abi_of.hpp>
#include <boost/config.hpp>
#include <type_traits>

namespace boost { namespace simd
{
  namespace detail
  {
    BOOST_SIMD_DEFINE_PACK_TRAITS(float         ,  4, __vector float          );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int32_t  ,  4, __vector signed   int   );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint32_t ,  4, __vector unsigned int   );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int16_t  ,  8, __vector signed   short );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint16_t ,  8, __vector unsigned short );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int8_t   , 16, __vector signed   char  );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint8_t  , 16, __vector unsigned char  );
    BOOST_SIMD_DEFINE_PACK_TRAITS(char          , 16, __vector unsigned char  );

    // Match also the bool funky types from VMX
    BOOST_SIMD_DEFINE_PACK_TRAITS(float         ,  4, __vector __bool int   );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int32_t  ,  4, __vector __bool int   );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint32_t ,  4, __vector __bool int   );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int16_t  ,  8, __vector __bool short );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint16_t ,  8, __vector __bool short );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int8_t   , 16, __vector __bool char  );
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint8_t  , 16, __vector __bool char  );
    BOOST_SIMD_DEFINE_PACK_TRAITS(char          , 16, __vector __bool char  );
  }

  namespace ext
  {
    template<typename Enable> struct abi_of<float,4,Enable>
    {
      using type = ::boost::simd::vmx_;
    };

    template<typename T, std::size_t N>
    struct abi_of<  T, N
                  , typename std::enable_if<   std::is_integral<T>::value
                                            && (N*sizeof(T) == 16) && (N > 2)
                                            >::type
                  >
    {
      using type = ::boost::simd::vmx_;
    };
  }
} }

#endif
