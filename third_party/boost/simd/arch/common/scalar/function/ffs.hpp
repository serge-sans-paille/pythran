//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FFS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FFS_HPP_INCLUDED

#include <boost/simd/detail/make_dependent.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( ffs_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type64_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;
    result_t operator() ( A0 a0) const
    {
      result_t t1 = bitwise_cast<result_t>(a0);

#ifdef __GNUC__
      return __builtin_ffsll(t1);
#elif defined BOOST_MSVC && defined _WIN64
      unsigned long index;
      if(_BitScanForward64(&index, uint64_t(t1)))
        return index+1;
      return 0;
#elif defined BOOST_MSVC
      unsigned long index;
      if (bitwise_and(t1, (uint64_t(-1) >> 32)))
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

  BOOST_DISPATCH_OVERLOAD ( ffs_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type32_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;

    result_t operator() ( A0 a0) const
    {
      result_t t1 = bitwise_cast<result_t>(a0);

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

  BOOST_DISPATCH_OVERLOAD ( ffs_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    using result_t = typename bd::as_integer_t<A0>;

    result_t operator() ( A0 a0) const
    {
      result_t t1 = bitwise_cast<result_t>(a0);
      using i_t = typename detail::make_dependent<uint32_t, A0>::type;
      return result_t(bs::ffs(i_t(t1)));
    }
  };
} } }


#endif
