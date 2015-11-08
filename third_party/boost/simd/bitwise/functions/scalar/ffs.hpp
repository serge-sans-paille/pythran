//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_FFS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_FFS_HPP_INCLUDED

#include <boost/simd/bitwise/functions/ffs.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#ifdef BOOST_MSVC
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_, (A0)
                            , (scalar_< type64_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);

    #ifdef __GNUC__
      return __builtin_ffsll(t1);
    #elif defined BOOST_MSVC && defined _WIN64
      unsigned long index;
      if(_BitScanForward64(&index, uint64_t(a0)))
        return index+1;
      return 0;
    #elif defined BOOST_MSVC
      unsigned long index;
      if (b_and(t1, (uint64_t(-1) >> 32)))
      {
        _BitScanForward(&index, uint32_t(t1));
        return index+1;
      }
      if(_BitScanForward(&index, uint32_t(t1 >> 32)))
        return index+1 + 32;
      return 0;
    #else
      if(!t1)
        return 0;

      // see http://supertech.csail.mit.edu/papers/debruijn.pdf
      const uint64_t magic = 0x03f79d71b4cb0a89ULL;
      static const unsigned int magictable[64] =
      {
         0,  1, 48,  2, 57, 49, 28,  3,
        61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22,
        45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16,
        54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10,
        25, 14, 19,  9, 13,  8,  7,  6,
      };

      return magictable[((t1&-t1)*magic) >> 58] + 1;
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_
                            , (A0)
                            , (scalar_< type32_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);

    #ifdef __GNUC__
      return __builtin_ffs(t1);
    #elif defined(BOOST_MSVC)
      unsigned long index;
      if(_BitScanForward(&index, t1))
        return index+1;
      return 0;
    #else
      if(!t1)
        return 0;

      // see http://supertech.csail.mit.edu/papers/debruijn.pdf
      static const uint32_t magic = 0x077CB531U;
      static const int magictable[32] =
      {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
      };

      return magictable[((t1&-t1)*magic) >> 27] + 1;
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ffs_, tag::cpu_ , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);
      typedef typename meta::make_dependent<uint32_t, A0>::type itype;
      return result_type(boost::simd::ffs(itype(t1)));
    }
  };
} } }

#endif

