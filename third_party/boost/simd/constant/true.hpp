//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TRUE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TRUE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the constant true.

    @return The True constant for the proper type
  **/
  template<typename T> T True();
} }
#endif

#include <boost/simd/constant/definition/true.hpp>
#include <boost/simd/arch/common/generic/constant/true.hpp>

#endif
