//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ULPDIST_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/constant/eps.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD_IF(ulpdist_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using itype = bd::as_integer_t<A0>;
        itype e1, e2;
        A0 m1, m2;
        std::tie(m1, e1) = pedantic_(ifrexp)(a0);
        std::tie(m2, e2) = pedantic_(ifrexp)(a1);
        itype expo = -bs::max(e1, e2);
        A0 e = if_else( bs::is_equal(e1, e2)
                      , bs::abs(m1-m2)
                      , bs::abs( bs::pedantic_(ldexp)(a0, expo)
                                 - bs::pedantic_(ldexp)(a1, expo))
                      );
        return if_zero_else(logical_or( logical_and(bs::is_nan(a0), bs::is_nan(a1))
                                      , bs::is_equal(a0, a1)
                                      )
                           , e/Eps<A0>()
                           );
      }
   };
} } }

#endif
