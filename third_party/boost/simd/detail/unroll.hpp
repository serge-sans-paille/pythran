//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_UNROLL_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_UNROLL_HPP_INCLUDED

#include <initializer_list>

#define BOOST_SIMD_LOCAL_UNROLL(STATEMENT)                                                         \
(void)std::initializer_list<int>{ ((STATEMENT),0)... }                                             \
/**/

#endif
