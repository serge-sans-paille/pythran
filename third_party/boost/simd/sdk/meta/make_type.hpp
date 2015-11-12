 //==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_MAKE_TYPE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_MAKE_TYPE_HPP_INCLUDED

#include <boost/config.hpp>

#ifdef BOOST_NO_RVALUE_REFERENCES
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_reference.hpp>
#endif

namespace boost { namespace simd { namespace meta
{
#ifdef BOOST_NO_RVALUE_REFERENCES

  template<class T>
  typename boost::disable_if< boost::is_reference<T>
                            , T const&
                            >::type
  make_type();

  template<class T>
  typename boost::enable_if< boost::is_reference<T>
                           , T
                           >::type
  make_type();

#else

  template<class T>
  T&& make_type();

#endif
} } }

#endif
