//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_MASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_MASK_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/mask.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // store data to a masked pointer from whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( store_
                          , (typename Src, typename Pointer, typename Zero, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer const& p) const
    {
      do_(s, p, typename Src::traits::element_range{});
    }

    template<typename... N>
    static BOOST_FORCEINLINE void do_(const Src& s, Pointer const& p, nsm::list<N...> const&)
    {
      auto const& m = p.mask();
      auto const& q = p.get();

      (void)(std::initializer_list<bool>
              {(extract<N::value>(m)  ? ((q[N::value] = extract<N::value>(s)),true): true)...}
            );
    }
  };

  //------------------------------------------------------------------------------------------------
  // store data to a masked pointer from whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( store_
                          , (typename Src, typename Pointer, typename Zero, typename X, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          , bd::scalar_<bd::integer_<A2>>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer const& p, A2 idx) const
    {
      ::boost::simd::store(s, mask( p.get()+idx, p.mask(), p.value()) );
    }
  };
} } }

#endif
