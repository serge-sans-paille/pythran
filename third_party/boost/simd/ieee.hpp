//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_IEEE_HPP_INCLUDED
#define BOOST_SIMD_IEEE_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-ieee Ieee functions

   These functions provide scalar and SIMD algorithms for inspecting, generating or
   decomposing IEEE 754 floating point numbers.

   Operations such as exponent and mantissa
   extraction, floating point modulo, IEEE bit patterns manipulation and
   magnitude comparison are provided.

<center>
 |                      |                  |                  |                 |                 |
 |:--------------------:|:----------------:|:----------------:|:---------------:|:---------------:|
 | @ref bitfloating     | @ref bitinteger  | @ref bitofsign   | @ref copysign   | @ref eps        |
 | @ref exponentbits    | @ref exponent    | @ref fpclassify  | @ref frac       | @ref frexp      |
 | @ref ifrexp          | @ref ilogb       | @ref ldexp       | @ref mantissa   | @ref maxmag     |
 | @ref maxnum          | @ref maxnummag   | @ref minmag      | @ref minnum     | @ref minnummag  |
 | @ref modf            | @ref negate      | @ref negatenz    | @ref nextafter  | @ref next       |
 | @ref nextpow2        | @ref predecessor | @ref prev        | @ref safe_max   | @ref safe_min   |
 | @ref saturate        | @ref sign        | @ref signnz      | @ref successor  | @ref ulpdist    |
 | @ref ulp             |                  |                  |                 |                 |
</center>
  **/

} }

#include <boost/simd/function/bitfloating.hpp>
#include <boost/simd/function/bitinteger.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/copysign.hpp>
#include <boost/simd/function/eps.hpp>
#include <boost/simd/function/exponentbits.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/fpclassify.hpp>
#include <boost/simd/function/frac.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/ilogb.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/mantissa.hpp>
#include <boost/simd/function/maxmag.hpp>
#include <boost/simd/function/maxnum.hpp>
#include <boost/simd/function/maxnummag.hpp>
#include <boost/simd/function/minmag.hpp>
#include <boost/simd/function/minnum.hpp>
#include <boost/simd/function/minnummag.hpp>
#include <boost/simd/function/modf.hpp>
#include <boost/simd/function/negate.hpp>
#include <boost/simd/function/negatenz.hpp>
#include <boost/simd/function/nextafter.hpp>
#include <boost/simd/function/next.hpp>
#include <boost/simd/function/nextpow2.hpp>
#include <boost/simd/function/predecessor.hpp>
#include <boost/simd/function/prev.hpp>
#include <boost/simd/function/safe_max.hpp>
#include <boost/simd/function/safe_min.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/function/sbits.hpp>
#include <boost/simd/function/sign.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/function/successor.hpp>
#include <boost/simd/function/ulpdist.hpp>
#include <boost/simd/function/ulp.hpp>

#endif
