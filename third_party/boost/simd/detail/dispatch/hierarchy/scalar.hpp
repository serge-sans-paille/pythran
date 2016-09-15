//==================================================================================================
/*!
  @file

  Defines the scalar_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SCALAR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SCALAR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy/generic.hpp>
#include <boost/simd/detail/dispatch/property_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Scalar types hierarchy tag

    The scalar_ hierarchy represents types which values are stored in one or multiple general
    purpose registers.

    @tparam Hierarchy Type hierarchy
  **/
  template<typename Hierarchy>
  struct  scalar_
#if !defined(DOXYGEN_ONLY)
        : scalar_<typename Hierarchy::parent>
#endif
  {
    using parent = scalar_<typename Hierarchy::parent>;
  };

#if !defined(DOXYGEN_ONLY)
  // When hitting unspecified_, behaves as a generic_ type
  template<typename Type>
  struct scalar_< unspecified_<Type> > : generic_<property_of_t<Type>>
  {
    using parent = generic_<property_of_t<Type>>;
  };
#endif
} }

#endif
