//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/shuffle/shuffler.hpp>
#include <boost/simd/arch/ppc/vmx/simd/function/topology.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd  =  boost::dispatch;
  namespace bs  =  boost::simd;
  namespace bsd =  boost::simd::detail;

  // -----------------------------------------------------------------------------------------------
  // Unary VMX shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::vmx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::fundamental_<A0>, bs::vmx_>
                          )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::vmx_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Binary VMX shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::vmx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::fundamental_<A0>, bs::vmx_>
                          , bs::pack_<bd::fundamental_<A0>, bs::vmx_>
                          )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const
    {
      return detail::shuffler<detail::vmx_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };
} } }

#endif
