//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_CHECK_PTR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_CHECK_PTR_HPP_INCLUDED

#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <algorithm>

#define BOOST_SIMD_DETAIL_MIN(A, B) (A) < (B) ? (A) : (B)

#define BOOST_SIMD_DETAILS_CHECK_PTR(Pointer, Alignment)                       \
BOOST_ASSERT_MSG( boost::simd::is_aligned                                      \
                        ( Pointer                                              \
                        , BOOST_SIMD_DETAIL_MIN                                \
                          ( std::size_t(Alignment)                             \
                          , std::size_t(BOOST_SIMD_CONFIG_ALIGNMENT)           \
                          )                                                    \
                        )                                                      \
                , "Unaligned memory location. You tried to access a "          \
                  "memory location which is not aligned properly with "        \
                  "respect to current alignment boundaries."                   \
                )                                                              \
/**/

#define BOOST_SIMD_DETAILS_CHECK_PTR_CVT(Pointer, SIMD, Scalar)                \
BOOST_SIMD_DETAILS_CHECK_PTR( Pointer                                          \
                            , BOOST_SIMD_DETAIL_MIN                            \
                              ( sizeof(SIMD)                                   \
                              , sizeof(SIMD) * sizeof(Scalar)                  \
                                            / sizeof(typename SIMD::value_type)\
                              )                                                \
                            )                                                  \
/**/

#endif
