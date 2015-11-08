//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_EPS_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_EPS_HPP_INCLUDED

#include <boost/simd/ieee/functions/eps.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#include <boost/simd/include/functions/simd/exponent.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::eps_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0&)const
    {
      return One<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::eps_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type int_type;
      typedef typename dispatch::meta::scalar_of<A0>::type sA0;
      result_type a = boost::simd::abs(a0);
      int_type e1 = exponent(a)-Nbmantissabits<A0>();
      result_type e =  bitwise_cast<result_type>(bitwise_cast<int_type>(One<A0>())+(shl(e1,Nbmantissabits<sA0>())));
      return seladd(is_invalid(a),
                select(boost::simd::is_less(a, Smallestposval<A0>()),
                     Mindenormal<A0>(), e),
                Nan<A0>());
    }
  };

} } }

#endif
