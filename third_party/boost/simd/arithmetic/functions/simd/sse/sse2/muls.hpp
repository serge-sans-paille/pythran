//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MULS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/simd/include/functions/simd/is_not_equal.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/split_multiplies.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

/* No native groups for 64-bit SSE;
 * we use bit tricks instead of calling saturate. */

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::muls_, boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<uint32_<A0>, boost::simd::tag::sse_>))
                                      ((simd_<uint32_<A0>, boost::simd::tag::sse_>))
                                    )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype res0, res1;
      split_multiplies(a0, a1, res0, res1);

      return group(res0, res1)
           | genmask( group( shrai(res0, sizeof(stype)*CHAR_BIT)
                           , shrai(res1, sizeof(stype)*CHAR_BIT)
                           )
                    );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::muls_, boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int32_<A0>, boost::simd::tag::sse_>))
                                      ((simd_<int32_<A0>, boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::as_unsigned<A0>::type untype;
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype res0, res1;
      split_multiplies(a0, a1, res0, res1);

      untype res2 = shrai(bitwise_cast<untype>(a0 ^ a1), sizeof(stype)*CHAR_BIT-1)
                  + static_cast<typename meta::scalar_of<untype>::type>(Valmax<stype>());

      A0 hi = group( shrai(res0, sizeof(stype)*CHAR_BIT)
                   , shrai(res1, sizeof(stype)*CHAR_BIT)
                   );
      A0 lo = group(res0, res1);

      return if_else( hi != shrai(lo, sizeof(stype)*CHAR_BIT-1)
                    , bitwise_cast<A0>(res2)
                    , lo
                    );
    }
  };
} } }

#endif
#endif
