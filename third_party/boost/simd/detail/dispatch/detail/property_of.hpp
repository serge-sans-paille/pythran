//==================================================================================================
/*!
  @file

  Defines the property_of metafunction extension point

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_DETAIL_PROPERTY_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_DETAIL_PROPERTY_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/sign_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy/integer_types.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy/ieee_types.hpp>
#include <boost/simd/detail/dispatch/hierarchy/void.hpp>
#include <boost/simd/detail/dispatch/hierarchy/bool.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <climits>

namespace boost { namespace dispatch { namespace ext
{
  /*!
    @ingroup group-extension
    @brief SFINAE-enabled extension point for property_of

    This extension point allows customization of the property_of @metafunction
    by letting user defined SFINAE-enabled context in which they can specialize
    property_of for family of types

    @par Usage:

    @tparam T       Scalar reference type used for discrimination
    @tparam Origin  Type being categorized
    @tparam Enable  SFINAE condition to be specified
  **/
  template<typename T, typename Origin, typename Enable = void>
  struct property_of
  {
    /// The property category of @c T
    using type = unspecified_<Origin>;
  };

  template<typename T, typename Origin>
  struct property_of< T, Origin
                    , typename std::enable_if<std::is_integral<T>::value>::type
                    >
  {
    using type = integral_<Origin, CHAR_BIT*sizeof(T), boost::dispatch::sign_of_t<T>>;
  };

  template<typename Origin> struct property_of<float, Origin>
  {
    using type = single_<Origin>;
  };

  template<typename Origin> struct property_of<double, Origin>
  {
    using type = double_<Origin>;
  };

  template<typename Origin> struct property_of<long double, Origin>
  {
    using type = long_double_<Origin>;
  };

  template<typename Origin> struct property_of<void, Origin>
  {
    using type = void_<Origin>;
  };

  template<typename Origin> struct property_of<bool, Origin>
  {
    using type = bool_<Origin>;
  };
} } }

#endif
