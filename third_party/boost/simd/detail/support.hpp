//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_SUPPORT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_SUPPORT_HPP_INCLUDED

namespace boost { namespace simd { namespace detail
{
  template<typename Extension> struct support
  {
    inline bool is_supported() const { return false; }
  };
} } }

#endif
