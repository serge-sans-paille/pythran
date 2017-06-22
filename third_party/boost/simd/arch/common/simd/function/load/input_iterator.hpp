//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/adapted/std/iterator.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load from a range of input iterator into a pack
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Begin, typename End, typename Ext)
                          , bd::cpu_
                          , bd::input_iterator_<bd::scalar_<bd::unspecified_<Begin>>>
                          , bd::input_iterator_<bd::scalar_<bd::unspecified_<End>>>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>, Ext>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    BOOST_FORCEINLINE target_t operator()(Begin const& b, End const&, Target const&) const
    {
      return do_(b, typename target_t::storage_kind(), typename target_t::traits::static_range{});
    }

    // Aggregate case: fill in the storage by calling load twice
    template<typename... N> static BOOST_FORCEINLINE
    target_t do_(Begin const& b, aggregate_storage const&, nsm::list<N...> const&)
    {
      // calling advance with an enum doesn't compile on MSVC
      std::ptrdiff_t off = target_t::traits::element_size;

      Begin b1 = b;
      std::advance(b1,off);

      Begin b2 = b1;
      std::advance(b2,off);

      return combine( load<typename target_t::substorage_type>(b,b1)
                    , load<typename target_t::substorage_type>(b1,b2)
                    );
    }

    template<typename N>
    static BOOST_FORCEINLINE auto value(Begin& b) -> decltype(*b++) { return *b++; }

    // Other case: Fill a pack piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_(Begin b, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      typename target_t::value_type p[sizeof...(N)] = { value<N>(b)... };
      return target_t( p[N::value]... );
    }
  };
} } }

#endif
