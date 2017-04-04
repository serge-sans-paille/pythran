//==================================================================================================
/*!
  @file

  Defines the property_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_PROPERTY_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_PROPERTY_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/detail/dispatch/detail/property_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-hierarchy
    @brief Retrieve the fundamental hierarchy of a Type

    For any type @c T, returns the hierarchy describing the fundamental properties of any given
    types. This Fundamental Hierarchy is computed by computing the hierarchy of the innermost
    embedded scalar type of @c T.

    @tparam T       Type to categorize
    @tparam Origin  Type to store inside the generated hierarchy type

    @par Models:

    @metafunction
  **/
  template<typename T, typename Origin = T>
  struct property_of
#if !defined(DOXYGEN_ONLY)
       : ext::property_of<scalar_of_t<T>, typename std::remove_reference<Origin>::type>
#endif
  {};

  /*!
    @ingroup group-hierarchy
    Eager short-cut to boost::dispatch::property_of
  **/
  template<typename T, typename Origin = T>
  using property_of_t = typename property_of<T,Origin>::type;
} }

#endif
