//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_VMX_FAST_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_VMX_FAST_RSQRT_HPP_INCLUDED
#if defined(BOOST_SIMD_HAS_VMX_SUPPORT)

#include <boost/simd/arithmetic/functions/fast_rsqrt.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(float a0) const
    {
      float r;
      __asm__ ("frsqrte %0, %1"
              : "=f" (r)
              : "f" (a0)
              );

      r *= ((3.0f - (r * r) * a0) * 0.5f);
      r *= ((3.0f - (r * r) * a0) * 0.5f);

      return r;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(double a0) const
    {
      double r;
      __asm__ ("frsqrte %0, %1"
              : "=f" (r)
              : "f" (a0)
              );

      r *= ((3.0f - (r * r) * a0) * 0.5f);
      r *= ((3.0f - (r * r) * a0) * 0.5f);
      r *= ((3.0f - (r * r) * a0) * 0.5f);

      return r;
    }
  };
} } }

#endif

#endif
