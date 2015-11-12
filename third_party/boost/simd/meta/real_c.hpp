//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_REAL_C_HPP_INCLUDED
#define BOOST_SIMD_META_REAL_C_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>

namespace boost { namespace simd { namespace meta
{
 template<typename Type, Type Value> struct real_c
 {
   BOOST_STATIC_CONSTANT(Type, value = Value);
   typedef real_c                                       type;
   typedef typename dispatch::meta::as_floating<Type>::type value_type;

   BOOST_FORCEINLINE operator value_type() const
   {
     return bitwise_cast<value_type>(Value);
   }
 };

} } }

#endif
