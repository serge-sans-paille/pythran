//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_DISPATCH_DETAIL_DECLVAL_HPP_INCLUDED
#define BOOST_DISPATCH_DETAIL_DECLVAL_HPP_INCLUDED

#include <boost/simd/detail/dispatch/config.hpp>

#ifdef BOOST_DISPATCH_USE_INCOMPLETE_STD
#  include <boost/utility/declval.hpp>
#else
#  include <utility>
#endif

namespace boost { namespace dispatch { namespace detail
{
#ifdef BOOST_DISPATCH_USE_INCOMPLETE_STD
  using boost::declval;
#else
  using std::declval;
#endif
} } }

#endif
