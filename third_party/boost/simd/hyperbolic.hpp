//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_HYPERBOLIC_HPP_INCLUDED
#define BOOST_SIMD_HYPERBOLIC_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-hyperbolic  Hyperbolic functions

    These functions provide scalar and SIMD version of
    hyperbolic  and inverse hyperbolic functions.

    All these functions can be included individually or all of them just by including <boost/simd/hyperbolic.hpp>

    - Direct hyperbolic functors

       <center>
         |               |              |                |              |
         |:-------------:|:------------:|:--------------:|:------------:|
         | @ref cosh     | @ref coth    | @ref csch      | @ref sech    |
         | @ref sinh     | @ref sinhc   | @ref sinhcosh  | @ref tanh    |
       </center>

          @ref sinhc is the hyperbolic sinus cardinal function
          (\f$\sinh x/x\f$).

          @ref sinhcosh  allows the simultaneous
          computation of hyperbolic sine and cosine at lower cost.

          @ref sech and @ref csch are the hyperbolic secant (inverse of
          the hyperbolic cosine) and cosecant (inverse of the hyperbolic sine)

           @par Example:

              @snippet direct_hyperbolic.cpp direct_hyperbolic

           @par Possible output:

              @snippet direct_hyperbolic.txt direct_hyperbolic

    - Inverse hyperbolic functors

       <center>
         |             |              |             |
         |:-----------:|:------------:|:-----------:|
         | @ref acosh  | @ref acoth   | @ref acsch  |
         | @ref asech  | @ref asinh   | @ref atanh  |
       </center>

         @par Example:

            @snippet inverse_hyperbolic.cpp inverse_hyperbolic

         @par Possible output:

            @snippet inverse_hyperbolic.txt inverse_hyperbolic


    **/

} }

#include <boost/simd/function/acosh.hpp>
#include <boost/simd/function/acoth.hpp>
#include <boost/simd/function/acsch.hpp>
#include <boost/simd/function/asech.hpp>
#include <boost/simd/function/asinh.hpp>
#include <boost/simd/function/atanh.hpp>
#include <boost/simd/function/cosh.hpp>
#include <boost/simd/function/coth.hpp>
#include <boost/simd/function/csch.hpp>
#include <boost/simd/function/sech.hpp>
#include <boost/simd/function/sinhc.hpp>
#include <boost/simd/function/sinhcosh.hpp>
#include <boost/simd/function/sinh.hpp>
#include <boost/simd/function/tanh.hpp>

#endif
