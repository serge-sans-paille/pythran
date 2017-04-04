//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
     This function object returns the number of non @ref Zero elements of the
   argument.


    @par Header <boost/simd/function/nbtrue.hpp>

    @par Note

     This function is peculiarly useful in horizontal branching idioms.

    @par Example:

      @snippet nbtrue.cpp nbtrue

    @par Possible output:

      @snippet nbtrue.txt nbtrue

  **/
  std::size_t nbtrue(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/nbtrue.hpp>
#include <boost/simd/function/simd/nbtrue.hpp>

#endif
