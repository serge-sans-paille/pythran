//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/arithmetic/functions/tofloat.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/bitwise_notand.hpp>
#include <boost/simd/include/constants/twoto31.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_cvtepi32_ps(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<uint64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    typedef typename meta::scalar_of<result_type>::type     stype;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::make<result_type> ( static_cast<stype>(a0[0])
                                            , static_cast<stype>(a0[1])
                                            );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_ , (A0)
                                    , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type  si_type;
      si_type a00 = bitwise_cast<si_type>(a0);
      si_type a01 = bitwise_notand(Signmask<si_type>(), a0);
      result_type inc = if_else_zero(is_ltz(a00), Twoto31<result_type>());
      return tofloat(a01)+inc;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type        result_type;
    typedef typename meta::scalar_of<result_type>::type           sftype;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::make<result_type> ( static_cast<sftype>(a0[0])
                                            , static_cast<sftype>(a0[1])
                                            );
    }
  };
} } }

#endif
#endif
