//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/operator/functions/is_greater.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_greater_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_<arithmetic_<A0>, boost::simd::tag::vmx_>))
                                      ((simd_<arithmetic_<A0>, boost::simd::tag::vmx_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_cmpgt(a0(),a1());
    }
  };
} } }

#endif
#endif
