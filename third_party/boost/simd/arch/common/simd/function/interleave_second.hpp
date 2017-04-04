//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slide.hpp>
#include <boost/simd/function/interleave_first.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    template<typename N, typename V>
    static BOOST_FORCEINLINE
    typename V::value_type value(V const& x, V const&, tt::true_type const&)
    {
      return bs::extract<V::static_size/2 + N::value/2>(x);
    }

    template<typename N, typename V>
    static BOOST_FORCEINLINE
    typename V::value_type value(V const&, V const& y, tt::false_type const&)
    {
      return bs::extract<V::static_size/2 + N::value/2>(y);
    }

    template<typename K, typename... N> static BOOST_FORCEINLINE
    T do_( T const& x, T const& y, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return T( value<N>(x,y, nsm::bool_<N::value%2==0>{})... );
    }

    template<typename K, typename N> static BOOST_FORCEINLINE
    T do_( T const& , T const& y, K const&, nsm::list<N> const&) BOOST_NOEXCEPT
    {
      return y;
    }

    template<typename... N> static BOOST_FORCEINLINE
    T do_( T const& x, T const& y, aggregate_storage const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      auto x0 = x.storage()[1];
      auto y0 = y.storage()[1];

      return  combine ( interleave_first( x0, y0)
                      , interleave_second(x0, y0)
                      );
    }

    BOOST_FORCEINLINE T operator()(T const& x, T const& y) const BOOST_NOEXCEPT
    {
      return do_(x,y, typename T::traits::storage_kind{}
                    , nsm::range<std::size_t, 0, T::static_size>{}
                );
    }
  };
} } }

#endif
