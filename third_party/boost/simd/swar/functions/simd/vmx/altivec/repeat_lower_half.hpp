//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_REPEAT_LOWER_HALF_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/repeat_lower_half.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::repeat_lower_half_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef A0                                    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      __vector unsigned char shft = { 0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7 };

      return vec_perm(a0(),a0(),shft);
    }
  };
} } }

#endif
#endif
