//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_STATS_MEDIAN_HPP_INCLUDED
#define NT2_SDK_BENCH_STATS_MEDIAN_HPP_INCLUDED

#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <string>

namespace nt2 { namespace bench { namespace stats
{
  /*!
    @brief Median statistic

    Used as a Metric parameter, median_ make the metric computes the
    median value of its samples.

    @note The median algorithm requires a minimal amount of samples to be
    correct. Currently, this minimum is set to 3 and any experiment providing
    less than this amount of samples will make use the average value of samples
    instead.
  **/
  struct median_
  {
    /// @brief Samples processing function
    template<typename Samples> static inline double evaluate(Samples const& d)
    {
      if( boost::accumulators::count(d) < 3 )
        return boost::accumulators::mean(d);
      else
        return boost::accumulators::median(d);
    }

    /// @brief Statistics display
    static inline std::string unit() { return " (med)"; }
  };
} } }

#endif
