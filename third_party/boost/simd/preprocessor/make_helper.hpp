//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_MAKE_HELPER_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_MAKE_HELPER_HPP_INCLUDED

#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BOOST_SIMD_MAKE_BODY(n)                                                \
typedef typename A0::type result_type;                                         \
typedef typename meta::scalar_of<result_type>::type stype;                     \
BOOST_FORCEINLINE result_type                                                  \
operator()(BOOST_PP_ENUM_PARAMS(n, stype const& a)) const                      \
/**/

#endif
