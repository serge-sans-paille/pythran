//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_CHAR_HELPER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_CHAR_HELPER_HPP_INCLUDED

#include <climits>

namespace boost { namespace simd { namespace ext
{
  template<class T>
  struct char_helper_impl
  {
    typedef T type;
  };

  template<class T>
  struct char_helper_impl<T const>
  {
    typedef typename char_helper_impl<T>::type const type;
  };

  template<>
  struct char_helper_impl<char>
  {
#if defined(CHAR_MIN) && (CHAR_MIN != 0)
    typedef signed char type;
#else
    typedef unsigned char type;
#endif
  };

  template<class T>
  BOOST_FORCEINLINE typename char_helper_impl<T>::type*
  char_helper(T* t)
  {
    return reinterpret_cast<typename char_helper_impl<T>::type*>(t);
  }
} } }

#endif
