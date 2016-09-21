//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_AS_SIMD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/arch/spec.hpp>

namespace boost { namespace simd { namespace detail
{
  //================================================================================================
  /*
    For a given couple Type x Cardinal, provides type and utility functions to handle data
    block containing Cardinal elements of type Type in an optimized way.
  */
  //================================================================================================
  template<typename Type, typename Extension> struct as_simd : ext::as_simd<Type,Extension> {};
} } }

#endif
