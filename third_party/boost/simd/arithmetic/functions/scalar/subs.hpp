//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SUBS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SUBS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/subs.hpp>
#include <boost/simd/include/functions/scalar/saturate.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/meta/as_signed.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::subs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0-a1;
    }
  };

  // for int8/int16
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::subs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< integer_<A0> >)
                                      (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype;
      typedef typename dispatch::meta::as_signed<utype>::type stype;
      return static_cast<result_type>(boost::simd::saturate<A0>(stype(a0)-stype(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::subs_, tag::cpu_
                                      , (A0)
                                      , (mpl::bool_<sizeof(A0) == 4 || sizeof(A0) == 8>)
                                      , (scalar_< uint_<A0> >)
                                        (scalar_< uint_<A0> >)
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 res = a0 - a1;
      res &= -(res <= a0);

      return res;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::subs_, tag::cpu_
                                      , (A0)
                                      , (mpl::bool_<sizeof(A0) == 4 || sizeof(A0) == 8>)
                                      , (scalar_<int_<A0> >)
                                        (scalar_<int_<A0> >)
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type utype;

      utype ux = a0;
      utype uy = a1;
      utype res = ux - uy;

      ux = (ux >> (sizeof(A0)*CHAR_BIT-1)) + Valmax<A0>();

      if(A0((ux ^ uy) & (ux ^ res)) < Zero<A0>())
        res = ux;

      return res;
    }
  };
} } }

#endif
