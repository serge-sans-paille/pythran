//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_TRAITS_HPP_INCLUDED

#include <boost/simd/arch/common/tags.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
  template<typename A0, typename A1>
  struct same_size
        : nsm::bool_<std::decay<A1>::type::static_size == std::decay<A0>::type::static_size>
  {};

  template<typename A0, typename A1>
  struct same_sizeof
        : nsm::bool_<sizeof(A0) == sizeof(A1)>
  {};

  template<typename X>
  struct is_native
        : nsm::bool_<!std::is_same<X,boost::simd::simd_emulation_>::value>
  {};
} } }

#endif
