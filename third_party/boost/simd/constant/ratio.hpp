//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_RATIO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_RATIO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant
    @brief Generate a constant from a static rational number representation.

    @tparam Type        Type of the generated constant
    @tparam Numerator   Numerator of the generated constant
    @tparam Denominator Denominator of the generated constant
  **/
  template<typename Type, std::uintmax_t Numerator, std::uintmax_t Denumerator> auto Ratio();
} }
#endif

#include <boost/simd/constant/definition/ratio.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_generator.hpp>
#include <boost/simd/arch/common/simd/constant/constant_generator.hpp>

#endif

