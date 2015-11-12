//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_ANDNOT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_andnot_
                                      , boost::simd::tag::avx_
                                      , (A0)(A1)
                                      , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                              , boost::simd::meta::cardinal_of<A1>
                                                              >
                                        )
                                      , ((simd_ < arithmetic_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        ((simd_ < arithmetic_<A1>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                              )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return vec_andc(a0(),simd::bitwise_cast<A0>(a1)());
    }
  };
} } }

#endif
#endif
