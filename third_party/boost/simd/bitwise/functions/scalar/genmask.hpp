//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_GENMASK_HPP_INCLUDED

#include <boost/simd/bitwise/functions/genmask.hpp>
#include <boost/simd/include/functions/scalar/unary_minus.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_, (A0)
                                   , (scalar_< fundamental_<A0> >)
                                   )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<result_type>::type itype;
      return bitwise_cast<result_type>(unary_minus(itype(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_, (A0)
                                   , (scalar_< arithmetic_<A0> >)
                                   )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<result_type>::type itype;
      return bitwise_cast<result_type>(unary_minus(itype(a0 != 0)));
    }
  };
} } }

#endif
