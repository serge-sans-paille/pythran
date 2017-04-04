//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/detail/constant/maxexponent.hpp>
#include <boost/simd/constant/nbexponentbits.hpp>
#include <boost/simd/detail/constant/pow2mask.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>, avx_>
                          , bs::pack_<bd::double_<A0>, avx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      using sA0 = bd::scalar_of_t<A0>;
      BOOST_ASSERT_MSG(assert_all(is_flint(a1)||is_invalid(a1)), "parameter is not a flint nor invalid");
      A0 oddv = fma(a1+Maxexponent<sA0>(), Two<sA0>(), (1 << (Nbexponentbits<sA0>()+1)) + 1);
      return a0*shift_left(bitwise_and(Pow2mask<A0>(), oddv), Nbexponentbits<sA0>());
    }
  };


} } }

#endif

