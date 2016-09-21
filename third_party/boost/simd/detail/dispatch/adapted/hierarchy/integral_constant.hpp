//==================================================================================================
/*!
  @file

  Provides a hierarchy for integral constant types

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_INTEGRAL_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_HIERARCHY_INTEGRAL_CONSTANT_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/scalar.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/property_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief integral constant type hierarchy tag

    Types are classified as constant_ if they are type embedding a integral constant.

    @note When reaching @c constant_<unspecified_<T>> , the hierarchy turns into
    @c scalar_<integral_<T>> and evolves accordingly.

    @tparam T Base hierarchy
  **/
  template<typename T>
  struct  constant_
#if !defined(DOXYGEN_ONLY)
        : constant_<typename T::parent>
#endif
  {
    using parent = constant_<typename T::parent>;
  };

#if !defined(DOXYGEN_ONLY)
  template<typename T>
  struct  constant_< unspecified_<T> > : scalar_<property_of_t<typename T::value_type,T> >
  {
    using parent = scalar_< property_of_t<typename T::value_type,T> >;
  };
#endif
} }

#endif
