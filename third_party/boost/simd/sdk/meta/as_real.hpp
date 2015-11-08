//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_AS_REAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_AS_REAL_HPP_INCLUDED

#include <boost/simd/sdk/meta/real_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct as_real
   : boost::mpl::apply1< typename boost::dispatch::meta::factory_of<T, typename scalar_of<T>::type>::type
                       , typename real_of<T>::type
                       >
  {};
} } }

#endif
