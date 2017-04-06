//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/logical.hpp>
#include <cstring>
#include <boost/simd/detail/nsm.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::generic_< bd::unspecified_<A0> >
                          , bd::target_< bd::generic_< bd::unspecified_<A1> > >
                          )
  {
    using result_t =  typename A1::type;

    static_assert ( (sizeof(A0) == sizeof(result_t))
                  , "boost.simd target is not same size as source in bitwise_cast"
                  );

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename std::is_same<A0, result_t>::type());
    }

    BOOST_FORCEINLINE result_t do_(A0 const& a0, tt::false_type const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename A0::storage_kind{});
    }

    BOOST_FORCEINLINE result_t do_(A0 const& a0, aggregate_storage const& ) const BOOST_NOEXCEPT
    {
      using tgt_t = typename result_t::template resize<result_t::static_size/2>;
      return combine( bitwise_cast<tgt_t>(slice_low(a0))
                    , bitwise_cast<tgt_t>(slice_high(a0))
                    );
    }

    template<typename K>
    BOOST_FORCEINLINE result_t do_(A0 const& a0, K const& ) const BOOST_NOEXCEPT
    {
      result_t that;
      std::memcpy(&that, &a0, sizeof(a0));
      return that;
    }

    BOOST_FORCEINLINE result_t do_(A0 const& a0, tt::true_type const& ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

} } }

#endif
