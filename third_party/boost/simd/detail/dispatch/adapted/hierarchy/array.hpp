//==================================================================================================
/*!
  @file

  Defines the array_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_ARRAY_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/adapted/hierarchy/tuple.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/property_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Array type hierarchy tag

    Types are classified as array_ if they represent a compound type with a static size,
    an operator[] and a value_type.

    @tparam T Base hierarchy
    @tparam N Size of the classified array
  **/
  template<typename T, typename N>
  struct  array_
#if !defined(DOXYGEN_ONLY)
        : array_<typename T::parent, N>
#endif
  {
    /// Parent hierarchy of array_
    using parent = array_<typename T::parent, N>;
  };

#if !defined(DOXYGEN_ONLY)
  template<typename T, typename N>
  struct  array_<unspecified_<T>,N> : bag_<property_of_t<T>, N>
  {
    using parent = bag_<property_of_t<T>, N>;
  };
#endif

} }

#endif
