//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DEINTERLEAVE_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/deinterleave_second.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  // r = [ a[0] a[2] ... a[n/2] b[0] b[2] ... b[n/2] ]

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints8_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints8_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  1, 3, 5, 7, 9,11,13,15
                                    , 17,19,21,23,25,27,29,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints16_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints16_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {   2, 3, 6, 7,10,11,14,15
                                    ,  18,19,22,23,26,27,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints32_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  4, 5, 6, 7,12,13,14,15
                                    , 20,21,22,23,28,29,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<single_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  4, 5, 6, 7,12,13,14,15
                                    , 20,21,22,23,28,29,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };
} } }

#endif
#endif
