//==================================================================================================
/*!
  @file

  Defines the formal_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_FORMAL_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_FORMAL_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Formal architecture hierarchy tag

    The formal_ hierarchy represents a 'virtual' hardware in which code transformation but
    no execution can take place. Functions defined on formal_ hardware are usually trampoline
    function that rewrite or transform code path.
  **/
  struct formal_ : unspecified_<formal_>
  {
    using parent        =  unspecified_<formal_>;
  };
} }

#endif
