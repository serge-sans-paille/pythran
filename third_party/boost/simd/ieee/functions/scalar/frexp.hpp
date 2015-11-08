//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/functions/scalar/bitwise_andnot.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>
#include <boost/simd/include/functions/scalar/shr.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>
#include <boost/simd/include/constants/maxexponentm1.hpp>
#include <boost/simd/include/constants/mask1frexp.hpp>
#include <boost/simd/include/constants/mask2frexp.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/include/functions/scalar/is_eqz.hpp>
#include <boost/simd/include/constants/twotonmb.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::frexp_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1>  >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0,A0 & r0,A1& r1) const
    {
      if (a0 == 0 || is_invalid(a0))
      {
        r0 = a0;
        r1 = Zero<A1>();
      }
      else
      {
        typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
        r1 = simd::bitwise_cast<int_type>(b_and(Mask1frexp<A0>(), a0));  // extract exp.
#ifndef BOOST_SIMD_NO_DENORMALS
        A1 t = Zero<A1>();
        if(is_eqz(r1)) // denormal
        {
          a0 *= Twotonmb<A0>();
          r1 = simd::bitwise_cast<int_type>(b_and(Mask1frexp<A0>(), a0));  // extract exp. again
          t = Nbmantissabits<A0>();
        }
#endif
        A0 x  = b_andnot(a0, Mask1frexp<A0>());                          // clear exp. in a0
        r1 = shri(r1,Nbmantissabits<A0>())- Maxexponentm1<A0>();         // compute exp.
        if (r1 > Limitexponent<A0>())
        {
          r1   = 0;
          r0   = a0;
          return;
        }
        r0 = b_or(x,Mask2frexp<A0>());                                    // insert exp.+1 in x
#ifndef BOOST_SIMD_NO_DENORMALS
        r1 -= t;
#endif
      }
    }
  };
} } }

#endif
