//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REPEAT_UPPER_HALF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REPEAT_UPPER_HALF_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD( repeat_upper_half_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    template<typename K, typename... N> static BOOST_FORCEINLINE
    T do_( T const& x, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return T( extract<N::value>(x)..., extract<N::value>(x)... );
    }

    template<typename K, typename N> static BOOST_FORCEINLINE
    T do_( T const& x, K const&, nsm::list<N> const&) BOOST_NOEXCEPT
    {
      return T( extract<N::value>(x) );
    }

    template<typename... N> static BOOST_FORCEINLINE
    typename T::storage_type
    do_( T const& x, aggregate_storage const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return  {{ x.storage()[1], x.storage()[1] }};
    }

    template<typename N> static BOOST_FORCEINLINE
    typename T::storage_type
    do_( T const& x, aggregate_storage const&, nsm::list<N> const&) BOOST_NOEXCEPT
    {
      return  {{ x.storage()[1], x.storage()[1] }};
    }

    BOOST_FORCEINLINE T operator()(T const& x) const BOOST_NOEXCEPT
    {
      return do_(x, typename T::traits::storage_kind{}
                  , nsm::range<std::size_t, T::static_size/2, T::static_size>{}
                );
    }
  };
} } }

#endif
