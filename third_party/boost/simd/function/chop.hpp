//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CHOP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CHOP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing chop capabilities

  chop (x, ndigits, base)
  truncate elements of x to a length of ndigits such that the
  resulting numbers are exactly divisible by base.  if base is not
  specified it defaults to 10.
  chop(x,n) chops aways from 0 to n digits:

  **/
  const boost::dispatch::functor<tag::chop_> chop = {};
} }
#endif

#include <boost/simd/function/scalar/chop.hpp>
#include <boost/simd/function/simd/chop.hpp>

#endif
