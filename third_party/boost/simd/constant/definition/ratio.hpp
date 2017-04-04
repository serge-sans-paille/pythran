//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_RATIO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_RATIO_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <cstdint>

namespace boost { namespace simd
{
  template<typename Type, std::uintmax_t Num, std::uintmax_t Denum>
  BOOST_FORCEINLINE Type Ratio()
  {
    return detail::constant ( detail::ratio< boost::dispatch::scalar_of_t<Type>, Num, Denum>{}
                            , boost::simd::as_<Type>{}
                            );
  }

  template<typename Type, std::uintmax_t Num>
  BOOST_FORCEINLINE Type Ratio()
  {
    return detail::constant ( detail::ratio< boost::dispatch::scalar_of_t<Type>, Num, 1>{}
                            , boost::simd::as_<Type>{}
                            );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Ratio(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Ratio<T>())
  {
    return Ratio<T>();
  }
} }

#endif
