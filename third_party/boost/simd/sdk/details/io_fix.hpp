//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DETAILS_IO_FIX_HPP_INCLUDED
#define BOOST_SIMD_SDK_DETAILS_IO_FIX_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T> inline
  typename  boost
            ::enable_if_c < (  boost::is_same<T,int8_t>::value
                            || boost::is_same<T,uint8_t>::value
                            || boost::is_same<T,char>::value
                            )
                          , int
                          >::type
  display ( T const& v)
  {
    return static_cast<int>(v);
  }

  template<class T> inline
  typename  boost
            ::disable_if_c< (  boost::is_same<T,int8_t>::value
                            || boost::is_same<T,uint8_t>::value
                            || boost::is_same<T,char>::value
                            )
                          , T const&
                          >::type
  display ( T const& v)
  {
    return v;
  }
} } }

#endif
