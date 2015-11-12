//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_STATS_AVERAGE_HPP_INCLUDED
#define NT2_SDK_BENCH_STATS_AVERAGE_HPP_INCLUDED

#include <boost/accumulators/statistics/mean.hpp>
#include <string>

namespace nt2 { namespace bench { namespace stats
{
  /*!
    @brief Average statistics

    Used as a Metric parameter, average_ make the metric computes the
    average value of its samples
  **/
  struct average_
  {
    /// @brief Samples processing function
    template<typename Samples> static inline double evaluate(Samples const& d)
    {
      return boost::accumulators::mean(d);
    }

    /// @brief Statistics display
    static inline std::string unit() { return " (avg)"; }
  };
} } }

#endif
