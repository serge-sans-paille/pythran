//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_LDEXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/ldexp.hpp>
#include <boost/simd/include/functions/scalar/shift_left.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/constant/constant_value.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ldexp_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< integer_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return (a1>0)?(a0<<a1):(a0>>a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ldexp_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    typedef typename dispatch::meta::as_integer<A0>::type iA0;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      iA0 e =  a1;
      A0 f = One<A0>();
#ifndef BOOST_SIMD_NO_DENORMALS
      if (BOOST_UNLIKELY((e < meta::constant_value<tag::Minexponent, A0>::value)))
      {
        e -= Minexponent<A0>();
        f = Smallestposval<A0>();
      }
#endif
      iA0 b = (e == Limitexponent<A0>());
      f += A0(b);
      e -= b;
      e += Maxexponent<A0>();
      e = shl(e, Nbmantissabits<A0>());
      return a0*bitwise_cast<A0>(e)*f;
    }
  };
} } }

#endif
