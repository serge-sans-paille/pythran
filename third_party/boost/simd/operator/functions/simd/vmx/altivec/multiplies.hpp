//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<single_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_madd(a0(),a1(), boost::simd::Mzero<A0>()());
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::vmx_, (A0)
                                    , ((simd_<type16_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<type16_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_mladd(a0(),a1(),Zero<A0>()());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::vmx_, (A0)
                                    , ((simd_<type8_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<type8_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type::native_type uptype;
      uptype l = vec_mule(a0(),a1());
      uptype r = vec_mulo(a0(),a1());
      return vec_mergel(vec_pack(l,l),vec_pack(r,r));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::vmx_, (A0)
                                    , ((simd_<uint32_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<uint32_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::downgrade<A0,unsigned>::type s_t;

      // reinterpret as u16
      s_t short0 = bitwise_cast<s_t>(a0);
      s_t short1 = bitwise_cast<s_t>(a1);

      // shifting constant
      typename A0::native_type shift_ = vec_splat_u32(-16);

      A0 sf = vec_rl(a1(), shift_);

      // Compute high part of the product
      A0 high    = vec_msum ( short0()
                            , bitwise_cast<s_t>(sf)()
                            , vec_splat_u32(0)
                            );

      // Complete by adding low part of the 16 bits product
      return vec_add( vec_sl(high(), shift_)
                    , vec_mulo(short0(), short1())
                    );
    }
  };
} } }

#endif
#endif
