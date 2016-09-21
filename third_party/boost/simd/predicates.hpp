//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_PREDICATES_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-predicates Predicates functions

      These functions provide scalar and SIMD algorithms for testing properties of values.
      Tests such as checks for validity, infinity, sign and others are provided. As for @ref
      group-boolean, these functions handle and return typed logical types.

      - These predicates can be used through an operator
      <center>
        | name                  |  op  | name               |  op   |
        |:---------------------:|:----:|:------------------:|:-----:|
        | @ref is_equal         | ==   | @ref is_less_equal |  <=   |
        | @ref is_greater_equal | >=   | @ref is_less       |  <    |
        | @ref is_greater       | >    | @ref is_not_equal  |  !=   |
      </center>

      - The following ones have to be called directly.

        Many of these are restriction to special values of some of the preceding ones.
        Their use often provides speed gain in SIMD mode.

      <center>
        | name                            | name                              | name                  |
        |:-------------------------------:|:---------------------------------:|:---------------------:|
        | @ref is_denormal                | @ref is_lez                       | @ref is_not_imag      |
        | @ref is_equal_with_equal_nans   | @ref is_ltz                       | @ref is_not_infinite  |
        | @ref is_eqz                     | @ref is_nan                       | @ref is_not_less_equal|
        | @ref is_even                    | @ref is_negative                  | @ref is_not_less      |
        | @ref is_finite                  | @ref is_nez                       | @ref is_not_nan       |
        | @ref is_flint                   | @ref is_ngez                      | @ref is_not_real      |
        | @ref is_gez                     | @ref is_ngtz                      | @ref is_odd           |
        | @ref is_gtz                     | @ref is_nlez                      | @ref is_ord           |
        | @ref is_imag                    | @ref is_nltz                      | @ref is_positive      |
        | @ref is_included_c              | @ref is_normal                    | @ref is_real          |
        | @ref is_included                | @ref is_not_denormal              | @ref is_simd_logical  |
        | @ref is_inf                     | @ref is_not_equal_with_equal_nans | @ref is_unord         |
        | @ref is_invalid                 | @ref is_not_greater               |                       |
        | @ref is_lessgreater             | @ref is_not_greater_equal         |                       |
      </center>


  **/

} }

#include <boost/simd/function/is_denormal.hpp>
#include <boost/simd/function/is_equal_with_equal_nans.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_even.hpp>
#include <boost/simd/function/is_finite.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_imag.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/is_less_equal.hpp>
#include <boost/simd/function/is_lessgreater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/is_negative.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/is_ngtz.hpp>
#include <boost/simd/function/is_nlez.hpp>
#include <boost/simd/function/is_nltz.hpp>
#include <boost/simd/function/is_normal.hpp>
#include <boost/simd/function/is_not_denormal.hpp>
#include <boost/simd/function/is_not_equal_with_equal_nans.hpp>
#include <boost/simd/function/is_not_greater_equal.hpp>
#include <boost/simd/function/is_not_greater.hpp>
#include <boost/simd/function/is_not_imag.hpp>
#include <boost/simd/function/is_not_infinite.hpp>
#include <boost/simd/function/is_not_less_equal.hpp>
#include <boost/simd/function/is_not_less.hpp>
#include <boost/simd/function/is_not_nan.hpp>
#include <boost/simd/function/is_not_real.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/is_ord.hpp>
#include <boost/simd/function/is_positive.hpp>
#include <boost/simd/function/is_real.hpp>
#include <boost/simd/function/is_unord.hpp>
#include <boost/simd/function/majority.hpp>

#endif

