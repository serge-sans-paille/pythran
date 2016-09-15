//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SPLITFACTOR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SPLITFACTOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  a constant used to split a floating number in two parts,
    in floating point routines (such @ref two_add and
    @ref two_prod) to get extra precision.

    @par Semantic:

    @code
    T r = Splitfactor<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 0
    else if T is double
      r =  pow(2, 27);
    else if T is float
      r =  pow(2, 13);
    @endcode

    @return The Splitfactor constant for the proper type
  **/
  template<typename T> T Splitfactor();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant splitfactor.

      @return The Splitfactor constant for the proper type
    **/
    Value Splitfactor();
  }
} }
#endif

#include <boost/simd/constant/definition/splitfactor.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
