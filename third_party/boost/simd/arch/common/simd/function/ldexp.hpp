//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/config.hpp>
#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/maxexponent.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/rshl.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/if_minus.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/fast.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/detail/constant/minexponent.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/if_minus.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(ldexp_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          , bs::pack_<bd::integer_<A1>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
     {
       return rshl(a0, a1);
     }
   };

  BOOST_DISPATCH_OVERLOAD(ldexp_
                         , (typename A0, typename A1, typename X)
                         , bd::cpu_
                         , bs::pack_<bd::integer_<A0>, X>
                         , bd::scalar_<bd::integer_<A1>>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, A1  a1) const BOOST_NOEXCEPT
    {
      using sA0 = bd::scalar_of_t<A0>;
      using iA0 = bd::as_integer_t<sA0>;
      return rshl(a0, iA0(a1));
    }
  };

  BOOST_DISPATCH_OVERLOAD(ldexp_
                             , (typename A0, typename A1, typename X, typename Y)
                             , bd::cpu_
                             , bs::pack_<bd::floating_<A0>, X>
                             , bs::pack_<bd::integer_<A1>, Y>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        using iA0 = bd::as_integer_t<A0>;
        using sA0 = bd::scalar_of_t<A0>;
        iA0 e = a1;
        A0 f = One<A0>();
  #ifndef BOOST_SIMD_NO_DENORMALS
        auto denormal =  is_less(e, Minexponent<A0>());
        e = if_minus(denormal, e, Minexponent<A0>());
        f = if_else(denormal, Smallestposval<A0>(), One<A0>());
  #endif
        auto test = is_equal(e, Limitexponent<A0>());
        f = if_plus(test, f, One<A0>());
        e = if_minus(test, e, One<iA0>());
        e += Maxexponent<A0>();
        e = shift_left(e, Nbmantissabits<sA0>());
        return a0*bitwise_cast<A0>(e)*f;
      }
   };

   BOOST_DISPATCH_OVERLOAD(ldexp_
                             , (typename A0, typename A1, typename X)
                             , bd::cpu_
                             , bs::pack_<bd::floating_<A0>, X>
                             , bd::scalar_<bd::integer_<A1>>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        using iA0 = bd::as_integer_t<A0>;
        using sA0 =  bd::scalar_of_t<A0>;
        using siA0 = bd::scalar_of_t<iA0>;
        siA0 e = a1;
        A0 f = One<A0>();
  #ifndef BOOST_SIMD_NO_DENORMALS
        auto denormal =  is_less(e, Minexponent<siA0>());
        e = if_minus(denormal, e, Minexponent<siA0>());
        f = if_else(denormal, Smallestposval<A0>(), One<A0>());
  #endif
        if (is_equal(e, Limitexponent<siA0>()))
        {
          f+= One<sA0>();
          e-= One<siA0>();
        }
        e += Maxexponent<sA0>();
        e = shift_left(e, Nbmantissabits<sA0>());
        return a0*(bitwise_cast<sA0>(e)*f);
      }
   };

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1, typename X, typename Y)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::integer_<A1>, Y>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &
                                    ,  const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      using sA0 = bd::scalar_of_t<A0>;
      i_t ik =  a1+Maxexponent<A0>();
      ik = shift_left(ik, Nbmantissabits<sA0>());
      return a0*bitwise_cast<A0>(ik);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bd::scalar_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &
                                    ,  const A0& a0,  A1 a1) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0>;
      using sA0 =  bd::scalar_of_t<A0>;
      using siA0 = bd::scalar_of_t<iA0>;
      siA0 ik =  a1+Maxexponent<sA0>();
      ik = shift_left(ik, Nbmantissabits<sA0>());
      return a0*A0(bitwise_cast<sA0>(ik));
    }
  };

} } }

#endif

