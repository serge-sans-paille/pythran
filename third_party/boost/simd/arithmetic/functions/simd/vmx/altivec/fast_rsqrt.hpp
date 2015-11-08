  //==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_FAST_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_FAST_RSQRT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/arithmetic/functions/rsqrt.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/fma.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type hf = Half<result_type>();
      result_type o  = One<result_type>();

      result_type estimate = vec_rsqrte( a0() );
      result_type se = sqr(estimate);
      result_type he = estimate*hf;
      result_type st = vec_nmsub(a0(),se(),o());

      return fma( st, he, estimate);
    }
  };
} } }

#endif

#endif

