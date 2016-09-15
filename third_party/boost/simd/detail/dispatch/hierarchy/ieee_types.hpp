//==================================================================================================
/*!
  @file

  Defines the type hierarchies for IEEE-754 like types

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_IEEE_TYPES_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_IEEE_TYPES_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/fundamental.hpp>
#include <boost/simd/detail/dispatch/hierarchy/sized_types.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief IEEE-754 double type hierarchy tag

    Types are classified as double_ if they behaves as a double precision IEEE-754 type.

    @tparam T Base hierarchy
  **/
  template<typename T> struct double_ : type64_<T>
  {
    using parent = type64_<T>;
  };

  /*!
    @ingroup group-tag
    @brief IEEE-754 single type hierarchy tag

    Types are classified as single_ if they behaves as a single precision IEEE-754 type.

    @tparam T Base hierarchy
  **/
  template<typename T> struct single_ : type32_<T>
  {
    using parent = type32_<T>;
  };

  /*!
    @ingroup group-tag
    @brief Long double type hierarchy tag

    Types are classified as long_double_ if they behaves as a long double type.

    @tparam T Base hierarchy
  **/
  template<typename T> struct long_double_ : fundamental_<T>
  {
    using parent = fundamental_<T>;
  };
} }

#endif
