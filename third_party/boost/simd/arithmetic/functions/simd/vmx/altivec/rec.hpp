//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_REC_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/arithmetic/functions/rec.hpp>
#include <boost/simd/include/functions/simd/fast_rec.hpp>
#include <boost/simd/include/functions/simd/copysign.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/dispatch/attributes.hpp>

#if !defined( BOOST_SIMD_NO_INFINITIES )
#include <boost/simd/include/functions/simd/is_inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_
                                   , boost::simd::tag::vmx_
                                   , (A0)
                                   , (( simd_ < floating_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                     ))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type estimate = fast_rec(a0);

      // fix rec(+/-0)
      estimate = if_else( is_eqz(a0)
                        , copysign(Inf<result_type>(),a0)
                        , estimate
                        );

      // fix rec(+/-inf)
      #if !defined( BOOST_SIMD_NO_INFINITIES )
      estimate = if_else( is_inf(a0)
                        , copysign(Zero<result_type>(),a0)
                        , estimate
                        );
      #endif

      return estimate;
    }
  };
} } }
#endif
#endif
