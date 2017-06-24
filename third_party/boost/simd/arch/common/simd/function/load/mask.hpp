//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_MASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_MASK_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/mask.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load data from a masked pointer of whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Pointer, typename Zero, typename Target, typename TX)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,TX>>
                          )
  {
    using target_t  = typename Target::type;

    BOOST_FORCEINLINE
    target_t operator()(Pointer const& p, Target const&) const
    {
      return do_(p, typename target_t::traits::element_range{});
    }

    template<typename... N> static BOOST_FORCEINLINE
    target_t do_(Pointer const& p, nsm::list<N...> const&)
    {
      using v_t = typename target_t::value_type;
      auto const& m = p.mask();
      auto const& v = p.value();
      auto const& q = p.get();

      return target_t ( static_cast<v_t>( extract<N::value>(m)  ? q[N::value]
                                                                : extract<N::value>(v)
                                        )...
                      );
    }
  };
} } }

#endif
