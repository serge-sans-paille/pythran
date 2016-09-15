//==================================================================================================
/*!
  @file

  Defines the arithmetic_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_ARITHMETIC_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_ARITHMETIC_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/fundamental.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief arithmetic type hierarchy tag

    Types are classified as arithmetic_ if the built-in arithmetic operators (+, -, *, /) are
    defined (possibly in combination with the usual arithmetic conversions).

    @tparam T Base hierarchy
  **/
  template<typename T> struct arithmetic_ : fundamental_<T>
  {
    using parent = fundamental_<T>;
  };
} }

#endif
