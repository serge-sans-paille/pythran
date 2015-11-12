//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FAST_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FAST_LDEXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/fast_ldexp.hpp>
#include <boost/simd/include/functions/scalar/shift_left.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_ldexp_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
       return (a1>=0)?(a0<<a1):(a0>>a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_ldexp_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<result_type>::type            sA0;
      typedef typename dispatch::meta::as_integer<A0>::type          iA0;
      iA0 ik =  a1+Maxexponent<A0>();
      ik = shl(ik, Nbmantissabits<sA0>());
      return a0*bitwise_cast<A0>(ik);
    }
  };
} } }


#endif
