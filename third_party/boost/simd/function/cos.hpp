//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the cosine of the input in radians.


    @par Header <boost/simd/function/cos.hpp>

    @par Notes
      The regular call to this functor is `cos(x)`,  but
    @c cos can also be called with two parameters as
      `cos(x, range_)` or with a decorator as `std_(cos)(x)` or `restricted_(cos)(x)`


    @c range_ is a tag that allows some control on the computation
      accuracy and speed.

      The control is on the reduction routine of the angle to the
      \f$[-\pi/4, \pi/4]\f$ interval.

      They actually are 3 reduction routines that respectively are
      sufficient for small_, medium_ and big_ angle values respecttively,
      to have (within
      cover test) one ulp of difference with the according crlibm
      (correctly rounded math library) result.

      Each tag covers respectively intervals \f$[-A, A]\f$ with :

      <center>
        |             |   float  A       |  double  A     |
        |:-----------:|:----------------:|:--------------:|
        |    small_   |    \f$20\pi\f$   | \f$20\pi\f$    |
        |    medium_  |   \f$2^6\pi\f$   | \f$2^{18}\pi\f$|
        |     big_    |   \f$\infty\f$   | \f$\infty\f$   |
      </center>

       In fact for each scalar singleton or simd vector of angles
       there are two possibilities :
       \arg one is to test if all vector element(s) are in the proper range
       for the consecutive increasing values of A until we reach a good
       one or the last :
       the corresponding template tags are @c small_, @c medium_ and @c big_
       \arg the second is to force directly a reduction method:
       the corresponding template tags are @c direct_small_, @c direct_medium_
       and @c direct_big_


       @par
       direct_small_ is NOT equivalent to small_ because there are also
       two other methods for \f$[0, \pi/4]\f$ (no reduction)
       and \f$[\pi/4, \pi/2]\f$
       (straight reduction) that are not considered in direct small_

       Note that for float the direct_big_ case is both early an hyper costly and
       shall be avoided whenever possible. To partially achieve this aim
       when double are available on the platform, this part of reduction
       is delegated to the double precision routines.

    @par Advices
       \arg If there is no restrictions ever on your angles and you care for precision
       use the default @c cos(x) or equivalently `cos(x, big_)`.
       \arg if you do not care for precision you can use
       `cos(x, medium_)` or `cos(x, small_)`
       that will be accurate for their proper range and degrade in accuracy
       with greater values.

       @par
       Now, the choice of direct or not relies on probabilities
       computations:
       assuming that a vector contains k elements and that testing all
       values that are in an interval takes c cycles and the probability of a value
       to be in interval \f$[a, b]\f$ is \f$p(a, b)\f$
       the number of cycles used by a
       direct\f${}_i\f$ method is simply the reduction time:
       \f$N(\f$direct\f${}_i)\f$
       On the other side the number of cycles for the non-direct methods will have a more
       complicated expression :

       \f$\hspace{5em}\sum_{i=1}^{m} p(A_{i-1}, A_i)^k N(\f$direct\f${}_i)\f$

       @par
       So the non direct methods will be interesting only if you want accurate
       results everywhere and have anyhow a big proportion of small angles.
       This is even more true (if possible) in simd and the more k is big, because
       of the kth power.

       @par
       For instance in the medium_ float case:

       \arg if angles are equidistributed  on \f$[0, 2^{16} \pi]\f$,
       the \f$p(0, 20\pi)\f$ will be
       less than \f$2^{-11}\f$ and thus (for example) if \f$k=4\f$,
       there will be 1 quadruple over 1.76e+13 falling in the small_ case...

       \arg Even sorting will do no good because the sort cost will be against
       the ratio of 1 successful quadruplet over 2048.
       \arg  Contrarily if your angles have a Gaussian distribution with 0 mean and
       \f$10\pi\f$ standard deviation,  80% of the intervals will be in the "small_"
       case (95% of the values).
       \arg Finally for those that are sure of their angles taking place in a fixed
       range and want speed, three other template tags can be of choice as they use
       the chosen reduction, but return Nan for any outsider.

       <center>
         `clipped_very_small_`, `clipped_small_` and `clipped_medium_`
       </center>

    @par Decorators

       - std_ provides access to std::cos

       - restricted_ is equivalent to the clipped_very_small_ tag

    @see  sincos, cosd, cospi

    @par Example:

      @snippet cos.cpp cos

    @par Possible output:

      @snippet cos.txt cos

  **/
  IEEEValue cos(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/cos.hpp>
#include <boost/simd/function/simd/cos.hpp>

#endif
