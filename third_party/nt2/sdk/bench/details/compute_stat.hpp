//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_COMPUTE_STAT_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_COMPUTE_STAT_HPP_INCLUDED

#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>

namespace nt2 { namespace details
{
  // Divisive metrics need to swap min and max for computation to be sensible
  template<typename S> struct compute_state
  {
    typedef S type;
  };

  template<> struct compute_state<nt2::bench::stats::min_>
  {
    typedef nt2::bench::stats::max_ type;
  };

  template<> struct compute_state<nt2::bench::stats::max_>
  {
    typedef nt2::bench::stats::min_ type;
  };
} }

#endif
