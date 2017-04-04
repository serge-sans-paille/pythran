//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TRUNC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the truncation toward @ref Zero
    of its parameter.


    @par Header <boost/simd/function/trunc.hpp>

    @par Notes
      - the call to `trunc(x)` is similar to `sign(x)*floor(abs(x))`

      - For floating point number it is also one of the two ouputs of
        the @ref modf function.
        And we have:
        @code
          trunc(x) + frac(x) == x;
        @endcode
        except for nans

    @par Decorators

       - std_ for floating entries call std::trunc

    @par Alias:

       fix

    @see abs, frac, floor, sign, modf, itrunc

    @par Example:

      @snippet trunc.cpp trunc

    @par Possible output:

      @snippet trunc.txt trunc

  **/
  Value trunc(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/trunc.hpp>
#include <boost/simd/function/simd/trunc.hpp>

#endif
