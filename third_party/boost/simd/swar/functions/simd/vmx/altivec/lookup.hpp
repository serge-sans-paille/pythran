//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOOKUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/lookup.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::vmx_
                                    , (A0)(A1)
                                    , ((simd_ < ints8_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < ints8_<A1>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A1::template rebind<unsigned char>::type u8type;
      return vec_perm(a0(),a0(), bitwise_cast<u8type>(a1)());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::vmx_
                                    , (A0)(A1)
                                    , ((simd_ < ints16_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < ints16_<A1>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A1::template rebind<unsigned char>::type u8type;
      typedef typename u8type::native_type                      u8n;

      // Compute proper permute mask by computing 2*a1/2*a1+1
      u8n v1  = bitwise_cast<u8type>(a1)();
      u8n inc = (u8n)(vec_splat_u16(1));
      u8n slt = {1,1,3,3,5,5,7,7,9,9,11,11,13,13,15,15};
      u8n msk = vec_add( inc, vec_sl(vec_perm(v1,v1,slt), vec_splat_u8(1)) );

      return vec_perm(a0(),a0(), msk);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::vmx_
                                    , (A0)(A1)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < ints32_<A1>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A1::template rebind<unsigned char>::type u8type;
      typedef typename u8type::native_type                      u8n;

      // Compute proper permute mask by computing 4*a1+0/1/2/3
      u8n v1  = bitwise_cast<u8type>(a1)();
      u8n inc = { 0,1,2,3,0,1,2,3, 0, 1, 2, 3, 0, 1, 2, 3 };
      u8n slt = { 3,3,3,3,7,7,7,7,11,11,11,11,15,15,15,15 };
      u8n msk = vec_add( inc, vec_sl( vec_perm(v1, v1, slt), vec_splat_u8(2)) );

      return vec_perm(a0(),a0(), msk);
    }
  };
} } }

#endif
#endif
