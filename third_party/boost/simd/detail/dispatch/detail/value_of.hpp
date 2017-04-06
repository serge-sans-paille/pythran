//==================================================================================================
/*!
  @file

  Defines the value_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_DETAIL_VALUE_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_DETAIL_VALUE_OF_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace ext
  {
    /*!
      @ingroup group-extension
      @brief SFINAE-enabled extension point for meta::value_of

      This extension point allows customization of the meta::value_of @metafunction
      by letting user defined SFINAE-enabled context in which they can specialize
      meta::value_of for family of types

      @par Usage:

      @tparam T       Type to build a Model @metafunction from
      @tparam Enable  SFINAE condition to be specified
    **/
    template<typename T, typename Enable> struct value_of
    {
      using type = T;
    };

    /*!
      @ingroup group-extension
      @brief SFINAE-enabled extension point for meta::value_of with qualifiers

      This extension point allows customization of the meta::value_of @metafunction
      by letting user defined SFINAE-enabled context in which they can specialize
      meta::value_of for family of types with cv-qualifiers

      @par Usage:

      @tparam T       Type to build a Model @metafunction from
      @tparam Enable  SFINAE condition to be specified
    **/
    template<typename T, typename Enable>
    struct value_of_cv<T const, Enable>
         : std::add_const<typename boost::dispatch::value_of<T>::type>
    {};

    template<typename T, typename Enable>
    struct value_of_cv<T&, Enable>
         : std::add_lvalue_reference<typename boost::dispatch::value_of<T>::type>
    {};

    template<typename T, typename Enable>
    struct value_of_cv<T&&, Enable>
         : std::add_rvalue_reference<typename boost::dispatch::value_of<T>::type>
    {};
  }
} }

#endif
