//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_CLZ_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_CLZ_HPP_INCLUDED

#include <boost/simd/bitwise/functions/clz.hpp>
#include <boost/simd/include/functions/scalar/ffs.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_MSVC
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_, (A0)
                            , (scalar_< type64_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        result_type t1 = bitwise_cast<result_type>(a0);
        BOOST_ASSERT_MSG( t1, "clz not defined for 0" );

      #ifdef __GNUC__
        return __builtin_clzll(t1);
      #else
        return boost::simd::ffs(reversebits(t1))-1;
      #endif
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_
                            , (A0)
                            , (scalar_< type32_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t1 = bitwise_cast<result_type>(a0);
      BOOST_ASSERT_MSG( t1, "clz not defined for 0" );

    #ifdef __GNUC__
      return __builtin_clz(t1);
    #else
      return boost::simd::ffs(reversebits(t1))-1;
     #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_
                            , (A0)
                            , (scalar_< type16_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type i_type;
      i_type t1 = bitwise_cast<i_type>(a0);
      return result_type(boost::simd::clz(uint32_t(t1))-16);
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_ , (A0)
                            , (scalar_< type8_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type i_type;
      i_type t1 = bitwise_cast<i_type>(a0);
      return result_type(boost::simd::clz(uint32_t(t1))-24);
    }
  };
} } }

#endif

