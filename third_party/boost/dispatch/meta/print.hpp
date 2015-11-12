//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PRINT_HPP_INCLUDED
#define BOOST_DISPATCH_META_PRINT_HPP_INCLUDED

#include <boost/config.hpp>

// Trick for GCC and Clang
#if (defined(__GNUC__) && !defined(BOOST_INTEL) && !defined(__CUDACC__))
namespace boost { namespace dispatch { namespace meta
{
  template<class T, int N = 0>
  struct print
  {
    typedef T type;
    unsigned : sizeof(T)*80;
  };
} } }
// Trick for MSVC (explicit cast to avoid having multiple warnings)
// generates both C4305 (/W1) and C4309 (/W2)
// use explicit casting to only generate C4310 (/W3)
#elif defined(BOOST_MSVC)
namespace boost { namespace dispatch { namespace meta
{
  template<class T, int N = 0>
  struct print
  {
    typedef T type;
    static const unsigned char generate_warning = /*(unsigned char)*/(sizeof(T)*300);
  };
} } }
// Otherwise, use boost::mpl::print
#else
#include <boost/mpl/print.hpp>
namespace boost { namespace dispatch { namespace meta
{
  template<class T, int N = 0>
  struct print : boost::mpl::print<T> {};
} } }
#endif

#endif

