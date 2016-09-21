//==================================================================================================
/*!
  @file

  Defines the integer_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_INTEGER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_INTEGER_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/arithmetic.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief integer type hierarchy tag

    Types are classified as integer_ if they behaves as one of the basic integral, non-boolean types.

    @tparam T Base hierarchy
  **/
  template<typename T> struct integer_ : arithmetic_<T>
  {
    using parent = arithmetic_<T>;
  };
} }

#endif
