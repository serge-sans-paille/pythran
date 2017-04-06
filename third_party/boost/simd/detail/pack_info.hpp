//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_INFO_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_INFO_HPP_INCLUDED

#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  // Overload for cardinal_of
  template<typename T, std::size_t N, typename ABI>
  struct cardinal_of<pack<T,N,ABI>> : tt::integral_constant<std::size_t,N>
  {};
} }

namespace boost { namespace dispatch { namespace detail
{
  // Overload for downgrade
  template<typename T, std::size_t N, typename ABI,typename Sign>
  struct  downgrade<boost::simd::pack<T,N,ABI>,Sign>
        : std::conditional< is_downgradable<T>::value
                          , boost::simd::pack<downgrade_t<T,Sign>, N*2>
                          , boost::simd::pack<T,N,ABI>
                          >
  {};

  // Overload for upgrade
  template<typename T, std::size_t N, typename ABI,typename Sign>
  struct upgrade<boost::simd::pack<T,N,ABI>,Sign>
        : std::conditional< is_upgradable<T>::value && (N/2 != 0)
                          , boost::simd::pack<upgrade_t<T,Sign>, N/2>
                          , boost::simd::pack<T,N,ABI>
                          >
  {};
} } }

#endif
