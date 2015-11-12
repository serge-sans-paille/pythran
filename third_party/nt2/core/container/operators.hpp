//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_OPERATORS_HPP_INCLUDED
#define NT2_CORE_CONTAINER_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/details/operators.hpp>

namespace nt2 { namespace container
{
 // unary operators
  using boost::simd::operator~;
  using boost::simd::operator!;
  using boost::simd::operator++;
  using boost::simd::operator--;

  // binary operators
  using boost::simd::operator&;
  using boost::simd::operator&=;
  using boost::simd::operator|;
  using boost::simd::operator|=;
  using boost::simd::operator^;
  using boost::simd::operator^=;
  using boost::simd::operator+;
  using boost::simd::operator+=;
  using boost::simd::operator-;
  using boost::simd::operator-=;
  using boost::simd::operator*;
  using boost::simd::operator*=;
  using boost::simd::operator/;
  using boost::simd::operator/=;
  using boost::simd::operator%;
  using boost::simd::operator%=;
  using boost::simd::operator<<;
  using boost::simd::operator<<=;
  using boost::simd::operator>>;
  using boost::simd::operator>>=;

  using boost::simd::operator&&;
  using boost::simd::operator||;

  // comparison operators
  using boost::simd::operator==;
  using boost::simd::operator!=;
  using boost::simd::operator<;
  using boost::simd::operator>;
  using boost::simd::operator<=;
  using boost::simd::operator>=;
} }

#endif
