//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NONE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NONE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
     This function object returns @c true if all elements of the argument are zero.


    @par Header <boost/simd/function/none.hpp>

    @par Example:

      @snippet none.cpp none

    @par Possible output:

      @snippet none.txt none

  **/
  bool none(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/none.hpp>
#include <boost/simd/function/simd/none.hpp>

#endif
