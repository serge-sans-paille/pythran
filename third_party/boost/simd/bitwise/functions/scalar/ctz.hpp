//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_CTZ_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_CTZ_HPP_INCLUDED

#include <boost/simd/bitwise/functions/ctz.hpp>
#include <boost/simd/include/functions/scalar/ffs.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_MSVC
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ctz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< type64_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      result_type that = bitwise_cast<result_type>(a0);
      BOOST_ASSERT_MSG( that, "ctz not defined for 0" );

      #if defined __GNUC__
      return __builtin_ctzll(that);
      #else
      return boost::simd::ffs(that)-1;
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ctz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< type32_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      result_type that = bitwise_cast<result_type>(a0);
      BOOST_ASSERT_MSG( that, "ctz not defined for 0" );

      #if defined __GNUC__
      return __builtin_ctz(that);
      #else
      return boost::simd::ffs(that)-1;
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ctz_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return result_type(boost::simd::ctz(uint32_t(a0)));
    }
  };
} } }

#endif

