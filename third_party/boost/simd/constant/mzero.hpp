//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MZERO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value -0

    @par Semantic:

    @code
    T r = Mzero<T>();
    @endcode

    is similar to:

    @code
    T r = -T(0);
    @endcode

    @ par Note:

    This is a special constant as it can be used and considered
    identical to zero, except that for floating point numbers,
    there is two different representation of zero with different bit of sign.

    The existence of the sign can be used in special circumstances as
    choosing between \f$+\infty\f$ and \f$-\infty\f$ instead of nan in computing 1/0.
    \par

    The sign of zero can be accessed through the @ref is_negative
    and @ref is_positive predicates or the @ref bitofsign functions.

    @return The Mzero constant for the proper type
  **/
  template<typename T> T Mzero();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant mzero.

      @return The Mzero constant for the proper type
    **/
    Value Mzero();
  }
} }
#endif

#include <boost/simd/constant/definition/mzero.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
