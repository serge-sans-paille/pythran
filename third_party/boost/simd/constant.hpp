//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_HPP_INCLUDED

/*!
  @ingroup group-functions
  @defgroup group-constant Constant Functions

  These functions provide scalar and SIMD constant generators for the most usual
  constant values such as zero, numeric limits, IEEE special values.

  Constant generator functions called by either:

  - taking no arguments but requiring a template type parameter
    so that the correct type of the constant is used:
    @code
    auto x = One<float>();
    @endcode

  - taking one type-arguments from which the correct type of the constant is deduced:
    @code
    double y = 0.;
    auto x = One( as(y) );
    @endcode
**/

#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/constant/bitincrement.hpp>
#include <boost/simd/constant/cgold.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/deginrad.hpp>
#include <boost/simd/constant/eight.hpp>
#include <boost/simd/constant/eps.hpp>
#include <boost/simd/constant/euler.hpp>
#include <boost/simd/constant/exp_1.hpp>
#include <boost/simd/constant/fact_10.hpp>
#include <boost/simd/constant/fact_11.hpp>
#include <boost/simd/constant/fact_12.hpp>
#include <boost/simd/constant/fact_4.hpp>
#include <boost/simd/constant/fact_5.hpp>
#include <boost/simd/constant/fact_6.hpp>
#include <boost/simd/constant/fact_7.hpp>
#include <boost/simd/constant/fact_8.hpp>
#include <boost/simd/constant/fact_9.hpp>
#include <boost/simd/constant/false.hpp>
#include <boost/simd/constant/five.hpp>
#include <boost/simd/constant/four.hpp>
#include <boost/simd/constant/fouropi.hpp>
#include <boost/simd/constant/fourpi.hpp>
#include <boost/simd/constant/fourthrooteps.hpp>
#include <boost/simd/constant/gold.hpp>
#include <boost/simd/constant/halfeps.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/inv2pi.hpp>
#include <boost/simd/constant/invexp_1.hpp>
#include <boost/simd/constant/invlog10_2.hpp>
#include <boost/simd/constant/invlog_10.hpp>
#include <boost/simd/constant/invlog_2.hpp>
#include <boost/simd/constant/invpi.hpp>
#include <boost/simd/constant/invsqrt_2pi.hpp>
#include <boost/simd/detail/constant/ldexpmask.hpp>
#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/log10_2hi.hpp>
#include <boost/simd/detail/constant/log10_2lo.hpp>
#include <boost/simd/detail/constant/log10_ehi.hpp>
#include <boost/simd/detail/constant/log10_elo.hpp>
#include <boost/simd/constant/log_10.hpp>
#include <boost/simd/constant/log10_pi.hpp>
#include <boost/simd/constant/log2_e.hpp>
#include <boost/simd/constant/log2_em1.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/constant/log_2olog_10.hpp>
#include <boost/simd/constant/logeps.hpp>
#include <boost/simd/constant/logpi.hpp>
#include <boost/simd/constant/logsqrt2pi.hpp>
#include <boost/simd/detail/constant/mantissamask.hpp>
#include <boost/simd/detail/constant/mask1frexp.hpp>
#include <boost/simd/detail/constant/mask2frexp.hpp>
#include <boost/simd/detail/constant/maxexponent.hpp>
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/detail/constant/maxflint.hpp>
#include <boost/simd/detail/constant/maxinit.hpp>
#include <boost/simd/detail/constant/maxleftshift.hpp>
#include <boost/simd/detail/constant/maxlog10.hpp>
#include <boost/simd/detail/constant/maxlog2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/detail/constant/medium_pi.hpp>
#include <boost/simd/constant/meight.hpp>
#include <boost/simd/constant/mfive.hpp>
#include <boost/simd/constant/mfour.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/mindenormal.hpp>
#include <boost/simd/detail/constant/minexponent.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/detail/constant/minlog10.hpp>
#include <boost/simd/detail/constant/minlog2.hpp>
#include <boost/simd/detail/constant/minlog.hpp>
#include <boost/simd/constant/mlog10two2nmb.hpp>
#include <boost/simd/constant/mlog2two2nmb.hpp>
#include <boost/simd/constant/mlogeps2.hpp>
#include <boost/simd/constant/mlogtwo2nmb.hpp>
#include <boost/simd/constant/mnine.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/mseven.hpp>
#include <boost/simd/constant/msix.hpp>
#include <boost/simd/constant/mten.hpp>
#include <boost/simd/constant/mthree.hpp>
#include <boost/simd/constant/mtwo.hpp>
#include <boost/simd/constant/mzero.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/nbdigits.hpp>
#include <boost/simd/constant/nbexponentbits.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/nine.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/oneosqrt5.hpp>
#include <boost/simd/constant/oneosqrteps.hpp>
#include <boost/simd/constant/oneotwoeps.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/detail/constant/pio2_1.hpp>
#include <boost/simd/detail/constant/pio2_1t.hpp>
#include <boost/simd/detail/constant/pio2_2.hpp>
#include <boost/simd/detail/constant/pio2_2t.hpp>
#include <boost/simd/detail/constant/pio2_3.hpp>
#include <boost/simd/detail/constant/pio2_3t.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/detail/constant/pio_2lo.hpp>
#include <boost/simd/constant/pio_3.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/detail/constant/pio_4lo.hpp>
#include <boost/simd/constant/pio_6.hpp>
#include <boost/simd/detail/constant/pix2_1.hpp>
#include <boost/simd/detail/constant/pix2_2.hpp>
#include <boost/simd/detail/constant/pix2_3.hpp>
#include <boost/simd/detail/constant/powlargelim.hpp>
#include <boost/simd/detail/constant/powlowlim.hpp>
#include <boost/simd/constant/quarter.hpp>
#include <boost/simd/constant/radindeg.hpp>
#include <boost/simd/detail/constant/radindegr.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/constant/seven.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/constant/six.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/detail/constant/splitfactor.hpp>
#include <boost/simd/constant/sqrt_1o_5.hpp>
#include <boost/simd/constant/sqrt_2.hpp>
#include <boost/simd/constant/sqrt_2o_2.hpp>
#include <boost/simd/constant/sqrt_2o_3.hpp>
#include <boost/simd/constant/sqrt_2opi.hpp>
#include <boost/simd/constant/sqrt_2pi.hpp>
#include <boost/simd/constant/sqrteps.hpp>
#include <boost/simd/constant/sqrtpio_2.hpp>
#include <boost/simd/constant/sqrtsmallestposval.hpp>
#include <boost/simd/constant/sqrtvalmax.hpp>
#include <boost/simd/constant/tan_3pio_8.hpp>
#include <boost/simd/constant/tanpio_8.hpp>
#include <boost/simd/constant/ten.hpp>
#include <boost/simd/constant/third.hpp>
#include <boost/simd/constant/thirdrooteps.hpp>
#include <boost/simd/constant/threeeps.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/constant/threepio_4.hpp>
#include <boost/simd/constant/true.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/twoopi.hpp>
#include <boost/simd/constant/twopi.hpp>
#include <boost/simd/constant/twopio_3.hpp>
#include <boost/simd/constant/twoto31.hpp>
#include <boost/simd/constant/twotom10.hpp>
#include <boost/simd/constant/twotomnmbo_3.hpp>
#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/zero.hpp>

#endif
