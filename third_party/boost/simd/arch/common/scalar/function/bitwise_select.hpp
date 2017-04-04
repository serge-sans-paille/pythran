//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_SELECT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/bitwise_or.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( bitwise_select_
                            , (typename A0, typename A1)
                            , (nsm::bool_<sizeof(A0)==sizeof(A1)>)
                            , bd::cpu_
                            , bd::scalar_<bd::arithmetic_<A0> >
                            , bd::scalar_<bd::arithmetic_<A1> >
                            , bd::scalar_<bd::arithmetic_<A1> >
                            )
  {
    BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1, A1 const& a2) const BOOST_NOEXCEPT
    {
      return bitwise_or(bitwise_and(a1, a0), bitwise_andnot(a2,a0));
    }
  };
} } }


#endif
