//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPRECNEG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPRECNEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing exprecneg capabilities

    Computes the  function: \f$e^{-\frac1x}\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T r = exprecneg(x);
    @endcode

    is equivalent to
    @code
    T r = exp(-rec((x)));
    @endcode

    @see exp, exprecnegc

  **/
  Value exprecneg(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/exprecneg.hpp>
#include <boost/simd/function/simd/exprecneg.hpp>

#endif
