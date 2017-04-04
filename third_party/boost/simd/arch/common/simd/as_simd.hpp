//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_AS_SIMD_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  template<typename T, typename Extension, typename Enable = void> struct as_simd
  {
    using type = nsm::no_such_type_;
  };
} } }

#endif
