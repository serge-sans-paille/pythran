//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_IO_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_IO_HPP_INCLUDED

#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/evaluate.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for pack<T,C>
  ////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t C>
  BOOST_FORCEINLINE
  std::ostream& operator<<(std::ostream& os, pack<T,C> const& v )
  {
    return os << evaluate(v);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for SIMD expression
  ////////////////////////////////////////////////////////////////////////////
  template<class X,class T>
  BOOST_FORCEINLINE
  std::ostream& operator<<(std::ostream& os, expression<X,T> const& v )
  {
    return os << evaluate(v);
  }

} }

#endif
