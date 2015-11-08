//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/touint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/inc.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::touint_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<integer_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::touint_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      typedef typename dispatch::meta::as_integer<typename meta::scalar_of<A0>::type, signed>::type signed_integer;
      A0 sign_f = inc(splat<A0>(Valmax<signed_integer>()));
      result_type sign_i = inc(splat<result_type>(Valmax<signed_integer>()));
      return if_else(a0 < sign_f, bitwise_cast<result_type>(toint(a0)), bitwise_cast<result_type>(toint(a0 - sign_f)) + sign_i);
    }
  };
} } }

#endif
