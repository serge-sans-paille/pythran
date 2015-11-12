//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_ZERO_OR_FALSE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_ZERO_OR_FALSE_HPP_INCLUDED

#include <boost/simd/sdk/meta/is_logical.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T>
  BOOST_FORCEINLINE
  typename boost::disable_if< meta::is_logical<T>, T>::type
  Zero_or_False()
  {
    return Zero<T>();
  }

  template<class T>
  BOOST_FORCEINLINE
  typename boost::enable_if< meta::is_logical<T>, T>::type
  Zero_or_False()
  {
    return False<T>();
  }
} } }

#endif
