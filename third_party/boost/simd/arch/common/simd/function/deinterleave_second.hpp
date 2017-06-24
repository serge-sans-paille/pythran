\
//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/make.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    static_assert ( T::static_size >= 2
                  , "deinterleave_second requires at least two elements"
                  );

    template<typename K, typename... N> static BOOST_FORCEINLINE
    T do_( T const& x, T const& y, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return make(as_<T>{}, bs::extract<N::value*2+1>(x)..., bs::extract<N::value*2+1>(y)... );
    }

    template<typename N0, typename N1, typename... Ns> static BOOST_FORCEINLINE
    T do_( T const& x, T const& y, aggregate_storage const&, nsm::list<N0,N1,Ns...> const&) BOOST_NOEXCEPT
    {
      return  combine ( deinterleave_second(x.storage()[0],x.storage()[1])
                      , deinterleave_second(y.storage()[0],y.storage()[1])
                      );
    }

    BOOST_FORCEINLINE T operator()(T const& x, T const& y) const BOOST_NOEXCEPT
    {
      return do_(x,y, typename T::traits::storage_kind{}
                    , nsm::range<std::size_t, 0, T::static_size/2>{}
                );
    }
  };
} } }

#endif
