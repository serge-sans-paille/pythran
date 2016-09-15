//==================================================================================================
/*!
  @file

  Defines the downgrade meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_DOWNGRADE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/updowngrade.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <cstdint>

namespace boost { namespace dispatch
{
  namespace detail
  {
    // Use this map to transform to downgraded type
    using downgrade_map = brigand::map< brigand::pair<bool          , bool          >
                                      , brigand::pair<std::uint8_t  , std::uint8_t  >
                                      , brigand::pair<std::uint16_t , std::uint8_t  >
                                      , brigand::pair<std::uint32_t , std::uint16_t >
                                      , brigand::pair<std::uint64_t , std::uint32_t >
                                      , brigand::pair<float         , float         >
                                      , brigand::pair<double        , float         >
                                      >;

    template<typename T,typename Sign>
    struct downgrade : boost::dispatch::detail::updowngrade<T,Sign,downgrade_map,false>
    {};

    template<typename T,typename Sign>
    struct downgrade<T&,Sign> : boost::dispatch::detail::downgrade<T,Sign> {};

    template<typename T,typename Sign>
    struct downgrade<T&&,Sign> : boost::dispatch::detail::downgrade<T,Sign> {};

    template<typename T,typename Sign>
    struct downgrade<T const,Sign> : boost::dispatch::detail::downgrade<T,Sign> {};
  }

  template<typename T,typename Sign = sign_of_t<T>>
  struct downgrade : detail::downgrade<T,Sign>
  {};

  template<typename T,typename Sign = sign_of_t<T>>
  using downgrade_t = typename downgrade<T,Sign>::type;

  template<typename T>
  struct is_downgradable : brigand::bool_<!std::is_same<T, typename downgrade<T>::type>::value>
  {};
} }

#endif
