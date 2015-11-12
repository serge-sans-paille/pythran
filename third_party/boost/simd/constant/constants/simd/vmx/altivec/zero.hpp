//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_VMX_ALTIVEC_ZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_VMX_ALTIVEC_ZERO_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/constant/constants/zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Zero
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < arithmetic_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      typedef typename result_type::template rebind<unsigned char>::type u8type;

      u8type z = vec_splat_u8(0);
      return bitwise_cast<result_type>( z );
    }
  };
} } }

#endif
#endif
