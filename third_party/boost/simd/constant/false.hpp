//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FALSE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FALSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates a value of the chosen type equals to @c false.

    @par Semantic:

    For type @c T modeling Logical
    @code
    T r = False<T>();
    @endcode

    is equivalent to:

    @code
    T r = false;
    @endcode

    @return A value of type @c T equals to @c false.

    @see functional::false
  **/
  template<typename T> T False();
} }
#endif

#include <boost/simd/constant/definition/false.hpp>
#include <boost/simd/arch/common/generic/constant/false.hpp>

#endif
