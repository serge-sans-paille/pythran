//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_OUTPUT_HPP_INCLUDED
#define NT2_OPTIMIZATION_OUTPUT_HPP_INCLUDED

#include <cstddef>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace nt2 { namespace optimization
{
  template<typename T, typename R> struct output
  {
    T           minimum;
    R           value;
    std::size_t iterations_count;
    bool        successful;
    T           covar;
  };
} }

BOOST_FUSION_ADAPT_TPL_STRUCT
(
  (T)(R),
  (nt2::optimization::output)(T)(R),
  (T          , minimum)
  (R          , value)
  (std::size_t, iterations_count)
  (bool       , successful)
  (T          , covariance)
);

#endif
