//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_IO_HPP_INCLUDED
#define NT2_SDK_UNIT_IO_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/simd/sdk/details/io_fix.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/array.hpp>

namespace std
{
  template<typename T, typename A>
  inline std::ostream& operator<<(std::ostream& os, std::vector<T,A> const& v)
  {
    typedef typename std::vector<T,A>::const_iterator iterator_t;

    os << "\n";
    for(iterator_t it = v.begin(); it != v.end(); ++it)
      os << boost::simd::details::display(*it) << "  ";
    os << "\n";

    return os;
  }

  template<typename T1, typename T2>
  inline std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& xpr)
  {
    os << "["   << boost::simd::details::display(xpr.first)
       << ",  " << boost::simd::details::display(xpr.second)
       << "]";

    return os;
  }

  template<typename T>
  inline std::ostream& operator<<(std::ostream& os, nt2::meta::as_<T> const&)
  {
    os <<  "as_<" << nt2::type_id<T>() << ">";

    return os;
  }
}

namespace boost
{
  template<typename T, std::size_t N>
  inline std::ostream& operator<<(std::ostream& os, boost::array<T,N> const& v)
  {
    os << "\n";
    for(std::size_t i=0;i<N;++i)
      os << boost::simd::details::display(v[i]) << "  ";
    os << "\n";

    return os;
  }
}

#endif
