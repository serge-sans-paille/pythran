//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_FAST_DIVIDES_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_FAST_DIVIDES_HPP_INCLUDED

#include <boost/simd/operator/functions/fast_divides.hpp>

namespace nt2
{
  namespace tag
  {
    using boost::simd::tag::fast_divides_;
  }

  using boost::simd::fast_divides;
  using boost::simd::fast_div;
  using boost::simd::fast_rdiv;
}

#endif
