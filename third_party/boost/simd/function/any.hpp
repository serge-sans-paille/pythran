//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ANY_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ANY_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
   This function object returns @c true if at least one element of the
   argument is non zero.

    @par Header <boost/simd/function/any.hpp>

    @see all, none, nbtrue

    @par Example:

      @snippet any.cpp any

    @par Possible output:

      @snippet any.txt any

  **/
  bool any(Value const &x);
} }
#endif

#include <boost/simd/function/scalar/any.hpp>
#include <boost/simd/function/simd/any.hpp>

#endif
