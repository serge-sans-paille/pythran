//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>

#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/logical_notand.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/constants/maxexponentm1.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>
#include <boost/simd/include/constants/mask1frexp.hpp>
#include <boost/simd/include/constants/mask2frexp.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/constants/twotonmb.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::frexp_
                                      , tag::cpu_, (A0)(A1)(A2)(X)(Y)
                                      , ( boost::mpl::and_
                                          < boost::is_same<A0,A1>
                                          , boost::is_same
                                            < typename dispatch::meta
                                                        ::as_integer<A0>::type
                                            , A2
                                            >
                                          >
                                        )
                                      , ((simd_< floating_<A0>, X>))
                                        ((simd_< floating_<A1>, X>))
                                        ((simd_< integer_<A2>, Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & r0, A2 & r1) const
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::as_logical<int_type>::type                 bint_type;
      typedef typename meta::scalar_of<A0>::type                           s_type;


#ifndef BOOST_SIMD_NO_DENORMALS
      bA0 test = logical_and(lt(simd::abs(a0), Smallestposval<A0>()), is_nez(a0));
      A0 aa0 = if_else(test, Twotonmb<A0>()*a0, a0);
      A2 t = if_else_zero(test,Nbmantissabits<A0>());
#else
      A0 aa0 = a0;
#endif
      r1 = simd::bitwise_cast<int_type>(b_and(aa0, Mask1frexp<A0>())); //extract exp.
      A0  x   = b_andnot(aa0, Mask1frexp<A0>());
      r1  = shri(r1,Nbmantissabits<s_type>()) - Maxexponentm1<A0>();
      r0  = b_or(x,Mask2frexp<A0>());

      bA0       test0 = is_nez(aa0);
      bint_type test1 = gt(r1,Limitexponent<A0>());

      r1 = if_else_zero(logical_notand(test1, test0), r1);
#ifndef BOOST_SIMD_NO_DENORMALS
      r1 -= t ;
#endif
      r0 = if_else_zero(test0, seladd(test1,r0,aa0));
    }
  };
} } }

#endif
