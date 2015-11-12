//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_INTERLEAVE_ODD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_INTERLEAVE_ODD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/interleave_odd.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints8_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints8_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = { 1,17, 3,19, 5,21, 7,23
                                    , 9,25,11,27,13,29,15,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints16_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints16_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  2, 3,18,19,6 , 7,22,23
                                    , 10,11,26,27,14,15,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<ints32_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  4, 5, 6, 7,20,21,22,23
                                    , 12,13,14,15,28,29,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                     ((simd_<single_<A1>,boost::simd::tag::vmx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char shft = {  4, 5, 6, 7,20,21,22,23
                                    , 12,13,14,15,28,29,30,31
                                    };

      return vec_perm(a0(),a1(),shft);
    }
  };
} } }

#endif
#endif
