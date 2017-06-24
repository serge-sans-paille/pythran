//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_TRIGONOMETRIC_HPP_INCLUDED
#define BOOST_SIMD_TRIGONOMETRIC_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-trigonometric Trigonometric functions.


    Algorithms for computing scalar and SIMD version of
    trigonometric and inverse trigonometric functions and some utilities.

    All these functions can be included individually or all of them just by including <boost/simd/trigonometric.hpp>

    Except a meaningful case (namely  cospi,  as \f$\cos(\pi n) = (-1)^n\f$ for integral n)
    these functions are only provided for floating (scalar or SIMD) inputs.

    - **Direct trigonometric functors**

       <center>
         | name          | name         | name           | name         | name         | name         |
         |:-------------:|:------------:|:--------------:|:------------:|:------------:|:------------:|
         | @ref cos      | @ref cosd    | @ref cospi     | @ref cotd    | @ref cot     | @ref cotpi   |
         | @ref cscd     | @ref csc     | @ref cscpi     | @ref secd    | @ref sec     | @ref secpi   |
         | @ref sin      | @ref sinc    | @ref sincos    | @ref sincosd | @ref sincospi| @ref sincpi  |
         | @ref sind     | @ref sinpi   | @ref tan       | @ref tand    | @ref tan     | @ref tanpi   |
       </center>

          'pi' (resp. 'd') suffix indicates that the input is to be done in \f$\pi\f$ multiples (resp. degrees).

          @ref sinc and @ref sincpi are 2 versions of the sinus cardinal function
          (resp. \f$\frac{\sin x}{x}\f$ and \f$\frac{\sin \pi x}{\pi x}\f$).

          @ref sincos,  @ref sincosd and  @ref sincospi allow the simultaneous
          computation of sine and cosine at lower cost.

          @ref sec and @ref csc are the secant (inverse of the cosine) and cosecant
          (inverse of the sine)

           @par Example:

              @snippet direct_trigonometric.cpp direct_trigonometric

           @par Possible output:

              @snippet direct_trigonometric.txt direct_trigonometric

           All direct and inverse functions (except cardinal ones) are provided in  three flavours using respectively
           radian, degrees and \f$\pi\f$ multiples.

           Be aware that their uses are not equivalent (see the above results).

           To give another example: sinpi(1.0) is not equal to sin(Pi<double>()).

             - Pi<double>() is only an approximation of \f$\pi\f$ to 0.5 ulp and the reduction of the angle Pi<double>()
             between  \f$-\pi/4\f$ and  \f$\pi/4\f$  will lead to a
             non zero value and @ref sin will return this small value  (namely 1.22464679914735e-16)
             as \f$\sin x \sim x\f$ for small values.

             - 1.0 is an exact double value and the reduction of the angle 1.0 between  \f$-0.25\f$ and  \f$0.25\f$
             will lead to an exact 0.0 the sinus of which is exactly 0.0.

             - However the two results are correct to 0.5 ulp.

             - All this DOES NOT IMPLY that trigonometric functors taking degrees or \f$\pi\f$ multiples as inputs are more accurate
             than those taking radians. The value computed by sin(Pi<double>()) is the correct value up to 0.5ulp of the sine of the input
             (which is not equal to \f$\pi\f$).

    - **Inverse trigonometric functors**

       <center>
         | name        | name         | name        | name         | name         | name         |
         |:-----------:|:------------:|:-----------:|:------------:|:------------:|:------------:|
         | @ref acos   | @ref acosd   | @ref acospi | @ref acot    | @ref acotd   | @ref acsc    |
         | @ref acscd  | @ref acscpi  | @ref asec   | @ref asecd   | @ref asecpi  | @ref asin    |
         | @ref asind  | @ref asinpi  | @ref atan2d | @ref atan2   | @ref atan2d  | @ref atan2pi |
       </center>

          'pi' (resp. 'd') suffix indicates that the return value  is in \f$\pi\f$ multiples (resp. degrees).

            @par Example:

              @snippet inverse_trigonometric.cpp inverse_trigonometric

           @par Possible output:

              @snippet inverse_trigonometric.txt inverse_trigonometric

    - Conversion utilities

       @ref indeg converts radian in degree

       @ref inrad converts degree in radian


    - Reduction utilities

      The algorithms used here to compute sine or cosine functions have two main steps

      - reduction of the angle to the \f$[-\pi/4, \pi/4]\f$ interval (if expressed in radian)
        and calculation of the right quadrant.
      - evaluation of an approximation  polynomial on the reduced interval.

      The reduction of the angle when no information is known on the angle magnitude can be
      very costly.

      there actually are 4 reduction routines protocol that respectively are
      sufficient for small_, medium_ and big_ angle values to have within
      cover test one ulp of difference with the according crlibm
      (correctly rounded math library) result.

      In fact the standard reduction algorithm used is roughly (M is  \f$2^6\pi\f$ for float and
      \f$2^{18}\pi\f$  for double)

        - if (\f$|x|\f$ is in \f$[0, \pi/4]\f$) do nothing
        - else if (\f$|x|\f$ is in \f$[0, \pi/2]\f$) use @ref rem_pio2_straight
        - else if (\f$|x|\f$ is in \f$[0, 20\pi]\f$) use @ref rem_pio2_cephes
        - else if (\f$|x|\f$ is in \f$[0, M\pi]\f$)  use @ref rem_pio2_medium
        - else use @ref rem_pio2


       There also exists @ref rem_2pi that only computes the reduction of the radian angle
       between \f$[-\pi, \pi]\f$


  **/

} }

#include <boost/simd/function/acos.hpp>
#include <boost/simd/function/acosd.hpp>
#include <boost/simd/function/acospi.hpp>
#include <boost/simd/function/acot.hpp>
#include <boost/simd/function/acotd.hpp>
#include <boost/simd/function/acscd.hpp>
#include <boost/simd/function/acscpi.hpp>
#include <boost/simd/function/acotpi.hpp>
#include <boost/simd/function/acsc.hpp>
#include <boost/simd/function/asecd.hpp>
#include <boost/simd/function/asecpi.hpp>
#include <boost/simd/function/asec.hpp>
#include <boost/simd/function/asin.hpp>
#include <boost/simd/function/asind.hpp>
#include <boost/simd/function/asinpi.hpp>
#include <boost/simd/function/atan2.hpp>
#include <boost/simd/function/atan2d.hpp>
#include <boost/simd/function/atan2pi.hpp>
#include <boost/simd/function/atan.hpp>
#include <boost/simd/function/atand.hpp>
#include <boost/simd/function/atanpi.hpp>
#include <boost/simd/function/cos.hpp>
#include <boost/simd/function/cosd.hpp>
#include <boost/simd/function/cospi.hpp>
#include <boost/simd/function/cot.hpp>
#include <boost/simd/function/cotd.hpp>
#include <boost/simd/function/cotpi.hpp>
#include <boost/simd/function/cscd.hpp>
#include <boost/simd/function/csc.hpp>
#include <boost/simd/function/cscpi.hpp>
#include <boost/simd/function/indeg.hpp>
#include <boost/simd/function/inrad.hpp>
#include <boost/simd/function/rem_2pi.hpp>
#include <boost/simd/function/rem_pio2_cephes.hpp>
#include <boost/simd/function/rem_pio2.hpp>
#include <boost/simd/function/rem_pio2_medium.hpp>
#include <boost/simd/function/rem_pio2_straight.hpp>
#include <boost/simd/function/sec.hpp>
#include <boost/simd/function/secd.hpp>
#include <boost/simd/function/secpi.hpp>
#include <boost/simd/function/sinc.hpp>
#include <boost/simd/function/sincosd.hpp>
#include <boost/simd/function/sincos.hpp>
#include <boost/simd/function/sincospi.hpp>
#include <boost/simd/function/sincpi.hpp>
#include <boost/simd/function/sin.hpp>
#include <boost/simd/function/sind.hpp>
#include <boost/simd/function/sinpi.hpp>
#include <boost/simd/function/tan.hpp>
#include <boost/simd/function/tand.hpp>
#include <boost/simd/function/tanpi.hpp>

#endif
