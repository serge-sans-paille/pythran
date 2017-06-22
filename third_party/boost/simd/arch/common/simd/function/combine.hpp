//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMBINE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMBINE_HPP_INCLUDED

#include <boost/simd/function/make.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // combine(scalar,scalar)
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<T> >
                          , bd::scalar_< bd::unspecified_<T> >
                          )
  {
    BOOST_FORCEINLINE pack<T,2> operator()(T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return make(as_<pack<T,2>>{}, a,b);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // combine(pack<T,N>,pack<T,N>)
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    using result_t = typename T::template resize<2 * T::static_size>;

    template<typename... N>
    static BOOST_FORCEINLINE result_t do_ ( T const& a, T const& b, aggregate_storage const&
                                          , nsm::list<N...> const&
                                          ) BOOST_NOEXCEPT
    {
      result_t that;
      that.storage()[0] = a;
      that.storage()[1] = b;
      return that;
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE result_t do_ ( T const& a, T const& b, K const&
                                          , nsm::list<N...> const&
                                          ) BOOST_NOEXCEPT
    {
      return make(as_<result_t>{}
                 , bs::extract<N::value>(a)...
                 , bs::extract<N::value>(b)...
                 );
    }

    BOOST_FORCEINLINE result_t operator()(T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return do_( a, b
                , typename result_t::traits::storage_kind{}
                , nsm::range<std::size_t, 0, T::static_size>{}
                );
    }
  };
} } }

#endif
