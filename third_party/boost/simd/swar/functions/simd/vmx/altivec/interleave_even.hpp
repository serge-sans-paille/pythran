//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_INTERLEAVE_EVEN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_INTERLEAVE_EVEN_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/interleave_even.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_even_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints8_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints8_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = { 0,16, 2,18, 4,20, 6,22
                                    , 8,24,10,26,12,28,14,30
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_even_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints16_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints16_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  0,1,16,17,4 , 5,20,21
                                    ,  8,9,24,25,12,13,28,29
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_even_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints32_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = { 0,1, 2, 3,16,17,18,19
                                    , 8,9,10,11,24,25,26,27
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_even_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<single_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = { 0,1, 2, 3,16,17,18,19
                                    , 8,9,10,11,24,25,26,27
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };
} } }

#endif
#endif
