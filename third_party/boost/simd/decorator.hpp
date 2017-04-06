//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DECORATOR_HPP_INCLUDED
#define BOOST_SIMD_DECORATOR_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-functions
    @defgroup group-decorator  Decorators


    @par Rationale
       Up to now we have five different decorators that can be used to
       modify the behaviour of some functors. Use of a functor with no decorator
       is often referred as "regular".

       These are pedantic_, raw_, restricted_,  saturated_, std_.
       (musl_ and plain_ also exist, but are used in an internal way).

       if a decorator `foo_` has to be called to modify the functor `bar` the call

         @code
          z = bar( < bar parameters > );
         @endcode

         has to be replaced by

         @code
          z = foo_(bar)(< bar parameters >);
         @endcode


    - raw_ implies

       possibly big loss of accuracy, loss of correctness for not "normal" values
       and no support for limiting cases. The purpose of raw_ is to maximize the speed
       using at hand functions (often intrinsics).

    - regular (no decorator) implies

        possibly a loss of correctness for not "normal" values (except zero) and
        limiting cases that are treated in a way not always conformant to standard (if it exists).
        The purpose of the regular way is to maximize the speed (but with few ulp losses
        with "normal" and zero parameters) and treating corner cases only if the
        performance loss is no more than a few percent.

    - pedantic_ implies

        if a standard exists the function is as conformant as possible whatever the
        loss in performances can be.

    - std_

        is reserved to the direct call of a libc++ version of the function: this means that
        in simd mode emulation is used. In general the performance is worse even in scalar mode.

    - saturated_

        is only efficient if the return type is Integral,  in which case the result is
        properly saturated

    - restricted_

        is used to indicate a restrained range of validity for a function. Up to now only
        direct trigonometic function can use this decorator which restricts their validity range to
        \f$[-\pi/4, \pi/4]\f$ (they return a nan outside),  but with an important speed-up.


    @par Note:
       Not "normal" values are as defined by the libc++ @c fpclassify by not returning
       @c FP_NORMAL, the categories being :

       <center>
       | result        |  meaning              |
       |:-------------:|:---------------------:|
       | FP_INFINITE   |  return "Inf";        |
       | FP_NAN        |  return "NaN";        |
       | FP_NORMAL     |  return "normal";     |
       | FP_SUBNORMAL  |  return "subnormal";  |
       | FP_ZERO       |  return "zero";       |
       </center>
  **/
#endif

} }

#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/restricted.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/function/std.hpp>

#endif
