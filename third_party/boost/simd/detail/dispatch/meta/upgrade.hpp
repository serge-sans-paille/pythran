//==================================================================================================
/*!
  @file

  Defines the upgrade meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_UPGRADE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_UPGRADE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/updowngrade.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <cstdint>

namespace boost { namespace dispatch
{
  namespace detail
  {
    // Use this map to transform to upgraded type
    using upgrade_map = nsm::map< nsm::pair<std::uint8_t  , std::uint16_t >
                                    , nsm::pair<std::uint16_t , std::uint32_t >
                                    , nsm::pair<std::uint32_t , std::uint64_t >
                                    , nsm::pair<std::uint64_t , std::uint64_t >
                                    , nsm::pair<float         , double        >
                                    , nsm::pair<double        , double        >
                                    >;

    template<typename T,typename Sign>
    struct upgrade : boost::dispatch::detail::updowngrade<T, Sign,upgrade_map,true>
    {};

    template<typename T,typename Sign>
    struct upgrade<T&,Sign> : boost::dispatch::detail::upgrade<T,Sign> {};

    template<typename T,typename Sign>
    struct upgrade<T&&,Sign> : boost::dispatch::detail::upgrade<T,Sign> {};

    template<typename T,typename Sign>
    struct upgrade<T const,Sign> : boost::dispatch::detail::upgrade<T,Sign> {};
  }

  template<typename T,typename Sign = sign_of_t<T>>
  struct upgrade : detail::upgrade<T,Sign>
  {};

  template<typename T,typename Sign = sign_of_t<T>>
  using upgrade_t = typename upgrade<T,Sign>::type;

  template<typename T>
  struct is_upgradable : nsm::bool_<!std::is_same<T, typename upgrade<T>::type>::value>
  {};
} }

#endif
