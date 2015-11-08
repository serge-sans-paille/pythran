//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_VMX_ALTIVEC_MTHREE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIMD_VMX_ALTIVEC_MTHREE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/constant/constants/mthree.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < int8_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_s8(-3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < uint8_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_u8(-3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < int16_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_s16(-3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < uint16_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_u16(-3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < int32_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_s32(-3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Mthree
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < uint32_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return vec_splat_u32(-3);
    }
  };
} } }

#endif
#endif
