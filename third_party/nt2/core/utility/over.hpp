//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OVER_HPP_INCLUDED
#define NT2_CORE_UTILITY_OVER_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/config.hpp>

namespace nt2
{
  BOOST_FORCEINLINE boost::array<std::ptrdiff_t,2> over(std::ptrdiff_t d)
  {
    boost::array<std::ptrdiff_t,2> that = {{d,1}};
    return that;
  }

  BOOST_FORCEINLINE boost::array<std::ptrdiff_t,2>
  over(std::ptrdiff_t d, std::ptrdiff_t b)
  {
    boost::array<std::ptrdiff_t,2> that = {{d,b}};
    return that;
  }
}

#endif
