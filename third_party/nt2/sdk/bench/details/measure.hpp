//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_MEASURE_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_MEASURE_HPP_INCLUDED

#include <nt2/sdk/timing/now.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <sstream>
#include <string>

namespace nt2 { namespace details
{
  // Type of accumulator used by all benchmarks
  typedef boost::accumulators::stats< boost::accumulators::tag::mean
                                      , boost::accumulators::tag::median
                                      , boost::accumulators::tag::min
                                      , boost::accumulators::tag::max
                                      , boost::accumulators::tag::count
                                      > stats_t;

  // accumulator for microseconds
  typedef boost::accumulators::accumulator_set<microseconds_t,stats_t>  times_set;

  // accumulator for CPU cycles
  typedef boost::accumulators::accumulator_set<cycles_t,stats_t>        cycles_set;


  // Compute an unique string referring to a proper Experiment result
  template<typename Experiment, typename Stat>
  inline std::string identify_result( std::string const& name
                                    , Experiment const& e
                                    , Stat const& s
                                    )
  {
    std::ostringstream str;
    str << name << e.size() << s.unit();
    return str.str();
  }
} }

#endif
