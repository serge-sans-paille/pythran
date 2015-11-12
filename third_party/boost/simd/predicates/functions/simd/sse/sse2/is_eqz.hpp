//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_EQZ_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_EQZ_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/predicates/functions/is_eqz.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/swar/functions/details/shuffle.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_eqz_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < int64_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::downgrade<A0>::type          base;

      const base tmp1 = boost::simd::bitwise_cast<base>(is_eqz(boost::simd::bitwise_cast<base>(a0)));
      const base tmp2 = details::shuffle<1,0,3,2>(tmp1);
      return boost::simd::bitwise_cast<result_type>(b_and(tmp1, tmp2));
    }
  };
} } }

#endif
#endif
