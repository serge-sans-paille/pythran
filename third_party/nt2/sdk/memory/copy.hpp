//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_COPY_HPP_INCLUDED
#define NT2_SDK_MEMORY_COPY_HPP_INCLUDED

#include <boost/detail/workaround.hpp>
#include <algorithm>
#include <iterator>

namespace nt2 { namespace memory
{
  /*!
   * Wrapper around copy to encapsulate various MSVC workaround
   *
   **/
  template<class In, class Out> inline void copy(In begin, In end, Out dst)
  {
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
    stdext::unchecked_copy(begin,end,dst);
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
    std::copy(begin,end, stdext::make_unchecked_array_iterator(dst));
#else
    std::copy(begin,end,dst);
#endif
  }

  /*!
   * Same as copy, but performs a cast to avoid warnings
   *
   **/
  template<class In, class Out> inline void cast_copy(In begin, In end, Out dst)
  {
    typedef typename std::iterator_traits<Out>::value_type T;
    for(; begin != end; ++begin)
      *dst++ = T(*begin);
  }

} }

#endif
