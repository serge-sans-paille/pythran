//==================================================================================================
/*!
  @file

  Defines the hierarchy_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/hierarchy_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-hierarchy
    @brief Retrieve the hierarchy of a Type

    For any type @c T, returns the hierarchy describing the properties of any given type.
    This Hierarchy can later be used to select functions implementation based on type properties.

    @par Models:

    @metafunction

    @tparam T       Type to categorize
    @tparam Origin  Type to store inside the generated hierarchy type
  **/
  template<typename T, typename Origin = T>
  struct  hierarchy_of
#if !defined(DOXYGEN_ONLY)
        : detail::hierarchy_of<T, typename std::remove_reference<Origin>::type>
#endif
  { };

  /*!
    @ingroup group-hierarchy
    Eager short-cut to boost::dispatch::hierarchy_of
  **/
  template<typename T, typename Origin = T>
  using hierarchy_of_t = typename hierarchy_of<T, Origin>::type;
} }

#endif
