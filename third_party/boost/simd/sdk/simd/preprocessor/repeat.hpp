//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PREPROCESSOR_REPEAT_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PREPROCESSOR_REPEAT_HPP_INCLUDED

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/for.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>

#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_PRED(r, data)                                              \
BOOST_PP_LESS_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, data), BOOST_PP_TUPLE_ELEM(4, 1, data))              \
/**/

#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_OP(r, data)                                                \
( BOOST_PP_ADD( BOOST_PP_TUPLE_ELEM(4, 0, data), BOOST_PP_TUPLE_ELEM(4, 0, data) )                 \
, BOOST_PP_TUPLE_ELEM(4, 1, data)                                                                  \
, BOOST_PP_TUPLE_ELEM(4, 2, data)                                                                  \
, BOOST_PP_TUPLE_ELEM(4, 3, data)                                                                  \
)                                                                                                  \
/**/

#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_MACRO(r, data)                                             \
BOOST_PP_TUPLE_ELEM(4, 2, data)(r, BOOST_PP_TUPLE_ELEM(4, 0, data), BOOST_PP_TUPLE_ELEM(4, 3, data)) \
/**/

/* Call \c m(z,n,data) with \c n all powers of 2 between \c from and \c to */
#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO(from, to, m, data)                                 \
BOOST_PP_FOR( (from, to, m, data)                                                                  \
            , BOOST_SIMD_PP_REPEAT_POWER_OF_2_PRED                                                 \
            , BOOST_SIMD_PP_REPEAT_POWER_OF_2_OP                                                   \
            , BOOST_SIMD_PP_REPEAT_POWER_OF_2_MACRO                                                \
            )                                                                                      \
/**/

/* Regular variants, go up to 32 */
#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(from, m, data) BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO(from, 32, m, data)
#define BOOST_SIMD_PP_REPEAT_POWER_OF_2(m, data) BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(1, m, data)

/* Big variant, goes up to 128 or 256 */
#ifdef __CUDACC__
#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_BIG(m, data)                                               \
BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO(1, 128, m, data)                                           \
/**/
#else
#define BOOST_SIMD_PP_REPEAT_POWER_OF_2_BIG(m, data)                                               \
BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO(1, 128, m, data)                                           \
m(7, 256, data)                                                                                    \
/**/
#endif

#endif
