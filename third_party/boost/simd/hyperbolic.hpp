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

    These functions provides scalar and SIMD version of
    hyperbolic  and inverse hyperbolic functions.

    - Direct hyperbolic functors

       <center>
         | name          | name         | name           | name         |
         |:-------------:|:------------:|:--------------:|:------------:|
         | @ref cosh     | @ref csch    | @ref sinh      | @ref sinhcosh|
         | @ref coth     | @ref sech    | @ref sinhc     | @ref tanh    |
       </center>

          @ref sinhc is the hyperbolic sinus cardinal function
          (\f$\sinh x/x\f$).

          @ref sinhcosh  allows the simultaneous
          computation of hyperbolic sine and cosine at lower cost.

          @ref sech and @ref csch are the hyperbolic secant (inverse of
          the hyperbolic cosine) and cosecant (inverse of the hyperbolic sine)

    - Inverse hyperbolic functors

       <center>
         | name        | name         | name        |
         |:-----------:|:------------:|:-----------:|
         | @ref acosh  | @ref acsch   | @ref asinh  |
         | @ref acoth  | @ref asech   | @ref atanh  |
       </center>
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
