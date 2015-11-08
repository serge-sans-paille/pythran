//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ULPDIST_HPP_INCLUDED
#include <boost/simd/ieee/functions/ulpdist.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>
#include <boost/simd/include/functions/scalar/ldexp.hpp>
#include <boost/simd/include/functions/scalar/frexp.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/include/functions/scalar/dist.hpp>
#include <boost/simd/include/functions/scalar/subs.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulpdist_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int_<A0> >)
                                      (scalar_< int_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a0>a1) ? subs(a0,a1) : subs(a1,a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulpdist_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint_<A0> >)
                                      (scalar_< uint_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return dist(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulpdist_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type itype;

      if (a0 == a1)               return Zero<A0>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<A0>();

      itype e1, e2;

      A0 m1 = boost::simd::frexp(a0, e1);
      A0 m2 = boost::simd::frexp(a1, e2);

      itype expo = -boost::simd::max(e1, e2);

      A0 e = (e1 == e2) ? boost::simd::abs(m1-m2)
                            :   boost::simd::abs( boost::simd::ldexp(a0, expo)
                                                - boost::simd::ldexp(a1, expo)
                                                );
      return e/Eps<A0>();
    }
  };
} } }

#endif
