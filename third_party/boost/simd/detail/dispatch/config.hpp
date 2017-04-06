//==================================================================================================
/*!
  @file

  Defines various macro for compiler-dependent attributes

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_CONFIG_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_CONFIG_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

// TODO : PR to Boost.config
#if defined(__GNUC__)
#define BOOST_RESTRICT __restrict__
#elif defined(_MSC_VER)
#define BOOST_RESTRICT __restrict
#else
#define BOOST_RESTRICT
#define BOOST_NO_RESTRICT
#endif

#if defined(BOOST_NO_RESTRICT) || defined(_MSC_VER)
#define BOOST_NO_RESTRICT_REFERENCES
#endif

#if defined(NSM_ASSUME_INCOMPLETE_STD)
#define BOOST_DISPATCH_USE_INCOMPLETE_STD
#endif

#endif
