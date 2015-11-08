//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_ROL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_ROL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/bitwise/functions/rol.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::rol_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < integer_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < integer_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "rol : rotation is out of range");

      typedef typename boost::dispatch::meta::as_unsigned<A0>::type c_t;

      return vec_rl(a0(), bitwise_cast<c_t>(a1)());
    }
  };
} } }

#endif
#endif
