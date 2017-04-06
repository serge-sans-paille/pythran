//==================================================================================================
/*!
  @file

  Defines the meta::scalar_of meta-function extension point

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_DETAIL_SCALAR_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_DETAIL_SCALAR_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
#if !defined(DOXYGEN_ONLY)
  namespace detail
  {
    template<typename T, typename U = boost::dispatch::value_of_t<T>>
    struct scalar_of : boost::dispatch::detail::scalar_of<U>
    {};

    template<typename T> struct scalar_of<T, T>
    {
      using type = T;
    };
  }
#endif

  namespace ext
  {
    /*!
      @ingroup group-extension
      @brief Extension point for scalar_of

      This extension point allows customization of the scalar_of @metafunction
      by letting the user specify how the @metafunction should behave on a given type.

      @tparam T Type to analyze
    **/
    template<typename T>
    struct scalar_of : boost::dispatch::detail::scalar_of<T>
    {};
  }
} }

#endif
