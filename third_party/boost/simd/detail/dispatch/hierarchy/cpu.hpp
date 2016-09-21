//==================================================================================================
/*!
  @file

  Defines the cpu_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_CPU_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_CPU_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/formal.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Basic architecture hierarchy tag

    The cpu_ hierarchy represents hardware with no specificities. Functions defined on cpu_
    hardware usually have common, hardware agnostic implementations.
  **/
  struct cpu_ : formal_
  {
    using parent = formal_;
  };
} }

#endif
