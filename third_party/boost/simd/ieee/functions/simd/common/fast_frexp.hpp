//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/constants/maxexponentm1.hpp>
#include <boost/simd/include/constants/mask1frexp.hpp>
#include <boost/simd/include/constants/mask2frexp.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::fast_frexp_
                                       , tag::cpu_
                                       , (A0)(A1)(X)(Y)
                                       , ( boost::is_same
                                           < typename  dispatch::meta
                                                       ::as_integer<A0>::type
                                           , A1
                                           >
                                         )
                                       , ((simd_< floating_<A0>, X>))
                                         ((simd_< floating_<A0>, X>))
                                         ((simd_< integer_<A1>, Y>))
                                       )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & r0,A1 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::scalar_of<A0>::type                      s_type;

      r1  = simd::bitwise_cast<int_type>(b_and(Mask1frexp<A0>(), a0));
      A0  x = b_andnot(a0, Mask1frexp<A0>());
      r1  = shr(r1,Nbmantissabits<s_type>()) - Maxexponentm1<A0>();
      r0  = b_or(x,Mask2frexp<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::fast_frexp_, tag::cpu_
                                       , (A0)(A1)(X)(Y)
                                       , ( boost::is_same
                                           < typename  dispatch::meta
                                                       ::as_integer<A0>::type
                                           , A1
                                           >
                                         )
                                       , ((simd_< floating_<A0>, X>))
                                         ((simd_< integer_<A1>, Y>))
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 & a2) const
    {
      A0 a1;
      boost::simd::fast_frexp(a0, a1, a2);
      return a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_frexp_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type exponent;
    typedef std::pair<A0,exponent>                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first;
      exponent second;
      boost::simd::fast_frexp(a0, first, second);
      return result_type(first, second);
    }
  };

} } }

#endif
