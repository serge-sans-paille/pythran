//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARITHMETIC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-arithmetic Arithmetic functions

    Those functions provides scalar and SIMD algorithms for classical arithmetic operators and
    functions provided by the C and C++ standard library. Other functions are also provided, in particular,
    provision for saturated operations through the use of a @ref decorator.

     - **Possibly saturated operations**

       The functors:
       <center>
         | name       | name            | name         | name             |
         |:----------:|:---------------:|:------------:|:----------------:|
         | @ref abs   | @ref minus      | @ref oneminus| @ref unary_minus |
         | @ref dec   | @ref multiplies | @ref sqr     | @ref unary_plus  |
         | @ref dist  | @ref plus       | @ref toint   | @ref touint      |
         | @ref inc   |                 |              |                  |
       </center>

       can be decorated with the  @ref saturated "saturated_" @ref decorator. This decorator has no effect on floating
       calls,  but on integer calls replaces the operation by its saturated equivalent.

       Typically overflows will be replaced by the @ref Valmin/@ref Valmax proper value instead of providing
       undefined behaviour for signed integral types or wrapping modulo Valmax+1 for unsigned ones.

       Peculiarly saturated_(@ref abs) and saturated_(@ref dist) ensure that the result will never be stricly
       negative (which is for instance the case of abs(Valmin<T>()) for T being any signed integral type).

       toint is a rather common operation as it converts floating number to signed integers of the same bit size,
       nevertheless it probably is its saturated version you have to use because it acts properly on large or not finite
       values, this is why an alias for saturated_(toint) is provided as @ref ifix.

     - **Rounding operations**
       <center>
         | name        | name            | name        | name             |
         |:-----------:|:---------------:|:-----------:|:----------------:|
         | @ref ceil   | @ref round      | @ref ifloor |  @ref inearbyint |
         | @ref floor  | @ref nearbyint  | @ref ifix   |                  |
         | @ref fix    | @ref iceil      | @ref iround |                  |
        </center>

          -The operations prefixed by 'i' return a value of the integral type associated to the entry type. (If T is
         the entry type it is @ref as_integer_t<T>)

          -The other ones return the same type as the entry.

     - **Division operations**

       @ref divides is the function associated to standard division. There is another one which provides more
       flexibility, namely rounded divisions.

       With two parameters @ref div and @ref divides are equivalent, but @ref div can admit a first option parameter
       that modifies its behaviour.

       The option parameter is described in the following table where a and b are of type T,  fT is a
       supposed floating type associated to T (@ref as_floating_t<T> if it exists) and iT is the integer type associated to T
       (@ref as_integer_t<T>). (fT and iT are here only to support pseudo code description)

       <center>
         | option             |          call            |      result similar to               |
         |--------------------|--------------------------|--------------------------------------|
         | @ref ceil          |   div(ceil, a, b)        |      T(ceil(fT(a)/fT(b)))            |
         | @ref floor         |   div(floor, a, b)       |      T(floor(fT(a)/fT(b)))           |
         | @ref fix           |   div(fix, a, b)         |      T(fix(fT(a)/fT(b)))             |
         | @ref round         |   div(round, a, b)       |      T(round(fT(a)/fT(b)))           |
         | @ref nearbyint     |   div(nearbyint, a, b)   |      T(nearbyint(fT(a)/fT(b)))       |
         | @ref iceil         |   div(iceil, a, b)       |      iT(iceil(fT(a)/fT(b)))          |
         | @ref ifloor        |   div(ifloor, a, b)      |      iT(ifloor(fT(a)/fT(b)))         |
         | @ref ifix          |   div(ifix, a, b)        |      iT(ifix(fT(a)/fT(b)))           |
         | @ref iround        |   div(iround, a, b)      |      iT(iround(fT(a)/fT(b)))         |
         | @ref inearbyint    |   div(inearbyint, a, b)  |      iT(inearbyint(fT(a)/fT(b)))     |
        </center>

     - **Remainder operations**

       @ref rem is the remander functor providing same kind of facilities as @ref div

       With two parameters rem(a, b) is equivalent to  rem(fix, a, b), but rem can admit
       a first optional parameter that modifies its behaviour and moreover can use the fast_ decorator if
       limiting case values are not a problem.

       The option parameter can be chosen between @ref ceil, @ref floor, @ref fix, @ref round, @ref nearbyint and if opt is the option,
       the call:

         rem(opt, a, b) is equivalent to a-b*div(opt, a, b)

       For floating entries the underlisted corner cases are handled in the following way (unless the @ref fast "fast_"
       decorator is used, the result in this case being undefined)
        -  if x is \f$\pm\infty\f$ , @ref Nan is returned
        -  if x is \f$\pm0\f$ and y is not 0 x is returned
        -  If y is \f$\pm0\f$, @ref Nan is returned
        -  If either argument is a nan, @ref a nan is returned

     - **complex operations**

       Boost.SIMD  does not provides complex number operations yet, but it will soon. So the following functors that
       have a meaning as a restriction to real number of complex functions, can be seen as a prequel:

      <center>
        | name        | name            | name        | name             | name             |
        |:-----------:|:---------------:|:-----------:|:----------------:|:----------------:|
        | @ref arg    | @ref conj       | @ref imag   | @ref real        | @ref sqr_abs     |
      </center>

        For real entries conj and real are identity,  imag always 0, sqr_abs coincide with sqr
        and arg results are always in the set \f$\{0, \pi,  Nan\}\f$

     - **Fused multiply-add operations**

      <center>
        | name            | name            | name         | name             |
        |:---------------:|:---------------:|:------------:|:----------------:|
        | @ref fma        | @ref fms        | @ref fnma    | @ref fnms        |
        | @ref correct_fma| @ref two_add,   | @ref two_prod| @ref two_split   |
      </center>

      Correct fused multiply/add implies

      - only one rounding
      - no "intermediate" overflow

      f?m? and fm? family provides this each time it is reasonable
      in terms of performance (mainly if the system has the hard
      wired capability).

      If you need "real" fma capabilities in all circumstances in your own
      code you can use @ref correct_fma (although it can be expansive) or
      (generally still more expansive) std_(fma) by using the decorator.

      @ref two_add, @ref two_prod and @ref two_split are used internally in @ref correct_fma and
      can be useful in searching extra-accuracy in other circumstances as double-double
      computations.

      @ref correct_fma is never used internally by Boost.SIMD

      - **Standard operations**

       The stdlibc++ provides them but only in scalar mode:

       <center>
         | name       | name            | name         |
         |:----------:|:---------------:|:------------:|
         | @ref abs   | @ref hypot      | @ref remquo  |
         | @ref ceil  | @ref max        | @ref round   |
         | @ref floor | @ref min        | @ref signbit |
         | @ref fma   | @ref rem (%)    | @ref sqrt    |
       </center>

       Boost.SIMD provides its own scalar and simd versions, but allows
       the use of the @ref std "std_" @ref decorator to call the associated system
       library function if the user needs it.

      - **Other operations**

       <center>
         | name         | name            | name          |
         |:------------:|:---------------:|:-------------:|
         | @ref average | @ref sqrt       | @ref tenpower |
         | @ref meanof  | @ref sqr        | @ref tofloat  |
         | @ref minmod  | @ref sqrt1pm1   |               |
       </center>
  **/
} }

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/arg.hpp>
#include <boost/simd/function/average.hpp>
#include <boost/simd/function/ceil.hpp>
#include <boost/simd/function/conj.hpp>
#include <boost/simd/function/correct_fma.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/dist.hpp>
#include <boost/simd/function/div.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/fix.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/fnma.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/hypot.hpp>
#include <boost/simd/function/iceil.hpp>
#include <boost/simd/function/ifix.hpp>
#include <boost/simd/function/ifloor.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/inearbyint.hpp>
#include <boost/simd/function/iround.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/meanof.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/minmod.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/rem.hpp>
#include <boost/simd/function/remquo.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/round.hpp>
#include <boost/simd/function/rsqrt.hpp>
#include <boost/simd/function/signbit.hpp>
#include <boost/simd/function/sqr_abs.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt1pm1.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/function/tenpower.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/touint.hpp>
#include <boost/simd/function/trunc.hpp>
#include <boost/simd/function/two_add.hpp>
#include <boost/simd/function/two_prod.hpp>
#include <boost/simd/function/two_split.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/unary_plus.hpp>


#endif
