//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_NEXTPOW2_HPP_INCLUDED

#include <boost/simd/ieee/functions/nextpow2.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/scalar/frexp.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>
#include <boost/simd/include/functions/scalar/minusone.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nextpow2_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < arithmetic_<A0> > )
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::nextpow2(tofloat(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nextpow2_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < floating_<A0> > )
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 m;
      result_type p;
      boost::simd::frexp(boost::simd::abs(a0), m, p);
      return (m == Half<A0>())  ? minusone(p) :  p;
    }
  };
} } }
#endif
