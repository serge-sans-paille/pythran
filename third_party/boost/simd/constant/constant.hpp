//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
/*!
    @ingroup group-constant
    Generates a value of the chosen type from an exact bits pattern.

    Constant generates a value from an exact bits pattern that get splat in the return
    value.

    @par Semantic:

    or any type @c T and any integral constant @c N :

    @code
    T r = Constant<T,N>();
    @endcode

    generates a values which bit pattern can be represent by the integer N.

    @tparam Type  Type of the desired value
    @tparam Bits  Bits pattern to generate as a value

    @return A value of type @c T which bits are exactly equals to @c N
  **/
  template<typename Type, std::uintmax_t Bits> auto Constant();
} }
#endif

#include <boost/simd/constant/definition/constant.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_generator.hpp>
#include <boost/simd/arch/common/simd/constant/constant_generator.hpp>

#endif
