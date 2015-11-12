//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/ldexp.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/rshl.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<integer_<A0>,X>))
                                         (generic_<integer_<A1> >)
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return rshl(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)(Y)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<floating_<A0>,X>))
                                         ((simd_<integer_<A1>,Y>))
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type  iA0;
      typedef typename meta::as_logical<iA0>::type           bA0;

      iA0 e = a1;
      A0 f = One<A0>();
#ifndef BOOST_SIMD_NO_DENORMALS
      bA0 denormal =  lt(e, Minexponent<A0>());
      e = selsub(denormal, e, Minexponent<A0>());
      f = if_else(denormal, Smallestposval<A0>(), One<A0>());
#endif
      bA0 test = eq(e, Limitexponent<A0>());
      f = seladd(test, f, One<A0>());
      e = selsub(test, e, One<iA0>());
      e += Maxexponent<A0>();
      e = shl(e, Nbmantissabits<A0>());
      return a0*bitwise_cast<A0>(e)*f;
    }
  };

} } }

#endif
