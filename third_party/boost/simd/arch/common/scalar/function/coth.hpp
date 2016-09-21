//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COTH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COTH_HPP_INCLUDED

#include <boost/simd/arch/common/detail/generic/tanh_kernel.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/coth.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( coth_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 5/8 sinh is computed using a polynomial(float)
      // (respectively rational(double)) approx inspirated from cephes.
      // else
      // coth(a0) is  sign(a0)*(1 + 2/(exp(2*x)-1))
      //////////////////////////////////////////////////////////////////////////////
      A0 x = bs::abs(a0);
      A0 r;
      if( x < Ratio<A0, 5, 8>())
      {
        r = detail::tanh_kernel<A0>::coth(x, sqr(x));
      }
      else
      {
        r = fma(Two<A0>(), rec(dec(exp(x+x))), One<A0>());
      }
      return bitwise_xor(r, bitofsign(a0));
    }
  };
} } }


#endif
