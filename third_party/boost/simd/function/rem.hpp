//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-operator

    This function object computes the remainder of the two parameters of the
    same type with or without option.

    @par Header <boost/simd/function/rem.hpp>

    @par Notes

    For any value @c a and @c b of same type `rem({option, }a, b)`
    returns the quotient of @c a by @c b respective to the option specified.

    - Options

      With no option this function is equivalent to `x-div(fix, x, y)*y`

      `option` may be @ref ceil, @ref floor, @ref fix, @ref round, @ref nearbyint (in the
      namespace booost::simd).
      Each option provides the same result as `x-div(option, x, y)*y`.

    - Supported types

      unsigned types are not supported but for the option @c fix, as in other cases results
      can be negative

    - Limiting values for floating entries:

       - if x is +/-inf , Nan is returned
       - if x is +/-0 and y is not 0, 0 is returned (if the sign of x matters the pedantic_
         decorated version returns x)
       - if y is +/-0, Nan is returned
       - if either argument is NaN, Nan is returned

    @par Decorators

      - pedantic_ insure better limiting cases (see above note)

      - std_ allow direct calls to some libc++ function:

        - option fix        calls std::fmod
        - option nearbyint  calls std::remainder
        - The other options have no standard equivalent

    @see div

    @par Example:

      @snippet rem.cpp rem

    @par Possible output:

      @snippet rem.txt rem


  **/
  Value rem(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/rem.hpp>
#include <boost/simd/function/simd/rem.hpp>

#endif
