//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_REAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_REAL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <cstdint>

namespace boost { namespace simd
{
  template<typename Type, detail::bits_t<double> Double, detail::bits_t<float> Single>
  BOOST_FORCEINLINE Type Real()
  {
    return detail::constant ( typename detail::constantify< boost::dispatch::scalar_of_t<Type>
                                                          , Double,Single
                                                          >::type{}
                            , boost::simd::as_<Type>{}
                            );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Real(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Real<T>())
  {
    return Real<T>();
  }
} }

#endif
