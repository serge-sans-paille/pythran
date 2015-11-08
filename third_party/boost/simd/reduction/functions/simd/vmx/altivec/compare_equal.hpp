//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_VMX_ALTIVEC_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_VMX_ALTIVEC_COMPARE_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/reduction/functions/compare_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::compare_equal_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<arithmetic_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef typename meta::as_logical<typename A0::value_type>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(vec_all_eq(a0(),a1()));
    }
  };
} } }

#endif
#endif
