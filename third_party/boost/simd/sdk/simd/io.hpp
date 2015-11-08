//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_IO_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_IO_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/extract.hpp>
#include <boost/simd/sdk/details/io_fix.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Stream insertion for swar types
  //////////////////////////////////////////////////////////////////////////////
  template<class S,class E> inline std::ostream&
  operator<<( std::ostream& os, native<S,E> const & v )
  {
    os << "( " << details::display(v[0]);
    for(std::size_t i=1;i<v.size();++i) os << "," << details::display(v[i]);
    os << " )";
    return os;
  }

} }

#endif
