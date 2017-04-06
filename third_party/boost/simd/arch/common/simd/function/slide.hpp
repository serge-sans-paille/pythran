//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/slice_low.hpp>
#include <boost/simd/function/slice_high.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  //------------------------------------------------------------------------------------------------
  // unary slide uses binary slide with Zero
  BOOST_DISPATCH_OVERLOAD( slide_
                          , (typename T, typename X, typename Offset)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    static BOOST_FORCEINLINE T do_(T const& a0, tt::true_type const&) BOOST_NOEXCEPT
    {
      return slide<Offset::value>(a0,Zero<T>());
    }

    static BOOST_FORCEINLINE T do_(T const& a0, tt::false_type const&) BOOST_NOEXCEPT
    {
      return slide<Offset::value+T::static_size>(Zero<T>(),a0);
    }

    BOOST_FORCEINLINE T operator()(T const& a0, Offset const&) const BOOST_NOEXCEPT
    {
      return do_(a0,nsm::bool_<(Offset::value >= 0)>());
    }
  };

  //------------------------------------------------------------------------------------------------
  // Binary slide reconstructs and optimizes
  BOOST_DISPATCH_OVERLOAD( slide_
                          , (typename T, typename X, typename Offset)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    using hcard = tt::integral_constant<std::size_t,T::static_size/2>;

    // Slide by N gives whatever in non-aggregate storage
    template<typename K, typename H, typename... L0, typename... L1>
    static BOOST_FORCEINLINE T unroll ( T const& a0, T const& a1, K const&, H const&
                                      , nsm::list<L0...> const&, nsm::list<L1...> const&
                                      )
    {
      // Sometimes, when L0 or L1 is empty, a0 or a1 can be unused and some compilers warns about it
      boost::ignore_unused(a0,a1);
      return T( extract<L0::value>(a0)..., extract<L1::value>(a1)... );
    }

    // Slide by N is optimized for aggregate storage
    template<typename... L0, typename... L1>
    static BOOST_FORCEINLINE T unroll ( T const& a0, T const& a1, aggregate_storage const&
                                      , tt::true_type const&
                                      , nsm::list<L0...> const&, nsm::list<L1...> const&
                                      )
    {
      return combine( slide<Offset::value%hcard::value>(a0.storage()[0], a0.storage()[1])
                    , slide<Offset::value%hcard::value>(a0.storage()[1], a1.storage()[0])
                    );
    }

    template<typename... L0, typename... L1>
    static BOOST_FORCEINLINE T unroll ( T const& a0, T const& a1, aggregate_storage const&
                                      , tt::false_type const&
                                      , nsm::list<L0...> const&, nsm::list<L1...> const&
                                      )
    {
      return combine( slide<Offset::value%hcard::value>(a0.storage()[1], a1.storage()[0])
                    , slide<Offset::value%hcard::value>(a1.storage()[0], a1.storage()[1])
                    );
    }

    BOOST_FORCEINLINE T operator()(T const& a0, T const& a1, Offset const&) const
    {
      // Those integral constant lists contain the iteration steps to be used by the variadic
      // unrolling seen above. We statically computes the indexes from a0 and a1 using their
      // relative position with respect to the slide offset.
      return unroll ( a0, a1, typename T::traits::storage_kind{}
                    , nsm::bool_<(Offset::value < hcard::value)>{}
                    , nsm::range<int,Offset::value, T::static_size>{}
                    , nsm::range<int,0, Offset::value>{}
                    );
    }
  };
} } }

#endif
