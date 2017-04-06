//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MANTISSAMASK_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MANTISSAMASK_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate a mask used to compute the mantissa of a floating point value


    @par Header <boost/simd/constant/mantissamask.hpp>

    @par Semantic:

    @code
    as_integer<T> r = Mantissamask<T>();
    @endcode

    @code
    if T is double
      r =  -2.225073858507200889e-308;
    else if T is float
      r =  -1.1754942106924410755e-38;
    @endcode

    @return The Mantissamask constant for the proper type
  **/
  template<typename T> T Mantissamask();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant mantissamask.

      @return The Mantissamask constant for the proper type
    **/
    Value Mantissamask();
  }
} }
#endif

#include <boost/simd/constant/scalar/mantissamask.hpp>
#include <boost/simd/constant/simd/mantissamask.hpp>

#endif
