//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/shuffle/shuffler.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // Unary singleton shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int Idx, typename A0)
                          , bd::cpu_
                          , bs::detail::pattern_<Idx>
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(bs::detail::pattern_<Idx> const&, A0 const& a0) const
    {
      static_assert ( Idx == -1 || Idx == 0
                    , "boost::simd::shuffle: Invalid permutation index"
                    );
      return detail::shuffler<void,bs::detail::pattern_<Idx>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Binary singleton shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int Idx, typename A0)
                          , bd::cpu_
                          , bs::detail::pattern_<Idx>
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    BOOST_FORCEINLINE
    A0 operator()(bs::detail::pattern_<Idx> const&, A0 const& a0, A0 const& a1) const
    {
      static_assert ( Idx == -1 || Idx == 0 || Idx == 1
                    , "boost::simd::shuffle: Invalid permutation index"
                    );
      return detail::shuffler<void,bs::detail::pattern_<Idx>>::process(a0,a1);
    }
  };
} } }

#endif
