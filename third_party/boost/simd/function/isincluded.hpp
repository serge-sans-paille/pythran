//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ISINCLUDED_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ISINCLUDED_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
    This function object returns @c true is only if all bits set in @c x are
  also set in @c y

    The two arguments must share the same bit size.


    @par Header <boost/simd/function/isincluded.hpp>

    @par Example:

      @snippet isincluded.cpp isincluded

    @par Possible output:

      @snippet isincluded.txt isincluded

  **/
  bool isincluded(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/isincluded.hpp>
#include <boost/simd/function/simd/isincluded.hpp>

#endif
