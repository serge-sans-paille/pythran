//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_FORWARD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_FORWARD_HPP_INCLUDED

#include <boost/proto/proto_fwd.hpp>
#include <boost/simd/sdk/simd/meta/native_cardinal.hpp>

namespace boost { namespace simd
{
  struct domain;
  template< class Type, class Cardinal> struct data;

  template< class Expression
          , class ResultType
          >
  struct expression;

  template< class Type
          , std::size_t Cardinal = meta::native_cardinal<Type>::value
          >
  struct pack;

} }

#endif
