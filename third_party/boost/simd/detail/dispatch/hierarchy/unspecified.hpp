//==================================================================================================
/*!
  @file

  Defines the unspecified_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_UNSPECIFIED_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_UNSPECIFIED_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/base.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Unspecified type hierarchy tag

    Types classified as unspecified_ provides no meaningful properties.
  **/
  template<typename T> struct unspecified_ : type_<T>
  {
    using parent = type_<T>;
  };
} }

#endif
