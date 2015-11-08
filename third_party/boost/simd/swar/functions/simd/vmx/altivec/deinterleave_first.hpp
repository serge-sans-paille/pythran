//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DEINTERLEAVE_FIRST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/deinterleave_first.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  // r = [ a[0] a[2] ... a[n/2] b[0] b[2] ... b[n/2] ]

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints8_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints8_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = { 0 , 2, 4, 6, 8,10,12,14
                                    , 16,18,20,22,24,26,28,30
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints16_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints16_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  0,1,4,5,8 ,9,12,13
                                    ,  16,17,20,21,24,25,28,29
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints32_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  0, 1, 2, 3, 8, 9,10,11
                                    , 16,17,18,19,24,25,26,27
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<single_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  0, 1, 2, 3, 8, 9,10,11
                                    , 16,17,18,19,24,25,26,27
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };
} } }

#endif
#endif
