//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CHOP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CHOP_HPP_INCLUDED

// #include <boost/simd/function/abs.hpp>
// #include <boost/simd/function/exp10.hpp>
// #include <boost/simd/function/floor.hpp>
// #include <boost/simd/function/inc.hpp>
// #include <boost/simd/function/is_eqz.hpp>
// #include <boost/simd/function/rec.hpp>
// #include <boost/simd/function/if_inc.hpp>
// #include <boost/simd/function/tofloat.hpp>
// #include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0)
//                           , bd::cpu_
//                           , bd::scalar_< bd::integer_<A0> >
//                           )
//   {
//     using result_t = A0;
//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0) const BOOST_NOEXCEPT
//     {
//       return a0;
//     }
//   };

//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0, typename A1)
//                           , bd::cpu_
//                           , bd::scalar_< bd::integer_<A0> >
//                           , bd::scalar_< bd::integer_<A1> >
//                           )
//   {
//     using result_t = A0;

//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
//     {
//       return toint(chop(tofloat(a0), a1));
//     }
//   };

//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0, typename A1)
//                           , bd::cpu_
//                           , bd::scalar_< bd::integer_<A0> >
//                           , bd::scalar_< bd::integer_<A1> >
//                           , bd::scalar_< bd::integer_<A2> >
//                           )
//   {
//     using result_t = A0;

//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
//     {
//       return toint(chop(tofloat(a0), a1, a2));
//     }
//   };


//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0)
//                           , bd::cpu_
//                           , bd::scalar_< bd::floating_<A0> >
//                           )
//   {
//     using result_t = A0;
//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0) const BOOST_NOEXCEPT
//     {
//       A0 tmp = if_inc(is_eqz(tmp), nt2::abs(x));
//       tmp = floor(inc(log10(tmp)));
//       inflate = exp10(- tmp);
//       A0 deflate = rec(inflate);
//       return deflate*chop(x*inflate);
//     }
//   };


//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0, typename A1)
//                           , bd::cpu_
//                           , bd::scalar_< bd::floating_<A0> >
//                           , bd::scalar_< bd::integer_<A1> >
//                           )
//   {
//     using result_t = A0;

//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
//     {
//       A0 tmp = if_inc(is_eqz(tmp), nt2::abs(x));
//       tmp = floor(inc(log10(tmp)));
//       inflate = exp10(tofloat(a1) - tmp);
//       return rec(inflate)*chop(x*inflate);
//     }
//   };

//   BOOST_DISPATCH_OVERLOAD ( chop_
//                           , (typename A0, typename A1)
//                           , bd::cpu_
//                           , bd::scalar_< bd::floating_<A0> >
//                           , bd::scalar_< bd::integer_<A1> >
//                           , bd::scalar_< bd::integer_<A2> >
//                           )
//   {
//     using result_t = A0;

//     BOOST_FORCEINLINE result_t operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
//     {
//       A0 tmp = if_inc(is_eqz(tmp), nt2::abs(x));
//       tmp = floor(inc(log10(tmp)));
//       inflate = exp10(tofloat(a1) - tmp);
//       return a2*rec(inflate)*chop(chop(x*inflate)/a2);
//     }
//   };

} } }


#endif
