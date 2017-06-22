//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_GATHER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_GATHER_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice_low.hpp>
#include <boost/simd/function/slice_high.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load by gathering data from a pointer of whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( load_
                          , ( typename Pointer
                            , typename Offset, typename X
                            , typename Target, typename TX
                            )
                          , bd::cpu_
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bs::pack_<bd::integer_<Offset>,X>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,TX>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    static_assert ( int(Offset::static_size) == int(target_t::static_size)
                  , "boost::simd::load - Mismatched gather offset cardinal"
                  );

    BOOST_FORCEINLINE
    target_t operator()(Pointer p, Offset const& o, Target const&) const BOOST_NOEXCEPT
    {
      return do_( p, o, typename target_t::storage_kind{}
                      , typename target_t::traits::static_range{}
                );
    }

    // Aggregate case: fill in the storage by calling gather twice
    template<typename... N> static BOOST_FORCEINLINE
    target_t do_( Pointer p, Offset const& o
                , aggregate_storage const&, nsm::list<N...> const&
                ) BOOST_NOEXCEPT
    {
      return combine( load<typename storage_t::value_type>(p, slice_low(o))
                    , load<typename storage_t::value_type>(p, slice_high(o))
                    );
    }

    // Other case: Fill a pack piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_(Pointer p, Offset const& o, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return target_t(static_cast<typename target_t::value_type>( p[ extract<N::value>(o) ])...);
    }
  };
} } }

#endif
