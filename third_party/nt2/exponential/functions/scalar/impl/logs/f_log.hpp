//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_LOG_HPP_INCLUDED

#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/exponential/functions/scalar/impl/logs/f_kernel.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/constants/log2_em1.hpp>
#include <nt2/include/constants/log10_ehi.hpp>
#include <nt2/include/constants/log10_elo.hpp>
#include <nt2/include/constants/log10_2hi.hpp>
#include <nt2/include/constants/log10_2lo.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/twotonmb.hpp>
#include <nt2/include/constants/mlogtwo2nmb.hpp>
#include <nt2/include/constants/mlog2two2nmb.hpp>
#include <nt2/include/constants/mlog10two2nmb.hpp>
#endif

namespace nt2 { namespace details
{
  template < class A0,
             class Style ,
             class base_A0 = typename meta::scalar_of<A0>::type>
             struct logarithm{};

  template < class A0 >
  struct logarithm< A0, tag::not_simd_type, float>
  {
    typedef typename meta::as_integer<A0, signed>::type    int_type;
    typedef typename meta::scalar_of<A0>::type                  sA0;
    typedef kernel<A0, tag::not_simd_type, float>          kernel_t;
    static inline A0 log(const A0& a0)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if (BOOST_UNLIKELY(a0 == nt2::Inf<A0>())) return a0;
#endif
      if (BOOST_UNLIKELY(nt2::is_eqz(a0))) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (BOOST_UNLIKELY(nt2::is_ltz(a0))) return nt2::Nan<A0>();
#else
      if (BOOST_UNLIKELY(nt2::is_nan(a0)||nt2::is_ltz(a0))) return nt2::Nan<A0>();
#endif
      A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 t = Zero<A0>();
      if(BOOST_UNLIKELY(nt2::abs(z) < Smallestposval<A0>()))
      {
        z *= Twotonmb<A0>();
        t = Mlogtwo2nmb<A0>();
      }
#endif
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y = nt2::fma(fe, Log_2lo<A0>(), y);
      y = nt2::fma(Mhalf<A0>(), x2, y);
#ifdef BOOST_SIMD_NO_DENORMALS
      return nt2::fma(Log_2hi<A0>(), fe, x+y);
#else
      return nt2::fma(Log_2hi<A0>(), fe, x+y+t);
#endif
    }

    static inline A0 log2(const A0& a0)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if (BOOST_UNLIKELY(a0 == nt2::Inf<A0>())) return a0;
#endif
      if (BOOST_UNLIKELY(nt2::is_eqz(a0))) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (BOOST_UNLIKELY(nt2::is_ltz(a0))) return nt2::Nan<A0>();
#else
      if (BOOST_UNLIKELY(nt2::is_nan(a0)||nt2::is_ltz(a0))) return nt2::Nan<A0>();
#endif
      A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 t = Zero<A0>();
      if (BOOST_UNLIKELY(nt2::abs(z) < Smallestposval<A0>()))
      {
        z *= Twotonmb<A0>();
        t = Mlog2two2nmb<A0>();
      }
#endif
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y = nt2::fma(Mhalf<A0>(),x2, y);
      z = nt2::fma(x,Log2_em1<A0>(),y*Log2_em1<A0>());
#ifdef BOOST_SIMD_NO_DENORMALS
      return ((z+y)+x)+fe;
#else
      return ((z+y)+x)+fe+t;
#endif
    }

    static inline A0 log10(const A0& a0)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if (BOOST_UNLIKELY(a0 == nt2::Inf<A0>())) return a0;
#endif
      if (BOOST_UNLIKELY(nt2::is_eqz(a0))) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (BOOST_UNLIKELY(nt2::is_ltz(a0))) return nt2::Nan<A0>();
#else
      if (BOOST_UNLIKELY(nt2::is_nan(a0)||nt2::is_ltz(a0))) return nt2::Nan<A0>();
#endif
      A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 t = Zero<A0>();
      if (BOOST_UNLIKELY(nt2::abs(z) < Smallestposval<A0>()))
      {
        z *= Twotonmb<A0>();
        t = Mlog10two2nmb<A0>();
      }
#endif
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y = nt2::amul(y, Mhalf<A0>(), x2);
      z = mul(x+y, Log10_elo<A0>());
      z = nt2::amul(z, y, Log10_ehi<A0>());
      z = nt2::amul(z, x, Log10_ehi<A0>());
      z = nt2::amul(z, fe, Log10_2hi<A0>());
#ifdef BOOST_SIMD_NO_DENORMALS
      return nt2::amul(z, fe, Log10_2lo<A0>());
#else
      return nt2::amul(z+t, fe, Log10_2lo<A0>());
#endif
    }
  };
} }


#endif
