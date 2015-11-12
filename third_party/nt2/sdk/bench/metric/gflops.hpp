//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_GFLOPS_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_GFLOPS_HPP_INCLUDED

#include <nt2/sdk/bench/details/compute_stat.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief GFLOPS per second metric

    This metric calculates the GFLOPS of a benchmark.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct gflops
  {
    /// @brief Evaluation of the metric in GFLOPS
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , nt2::details::times_set const&
                      , nt2::details::cycles_set const& c
                      ) const
    {
      unsigned long freq = get_cpu_freq();
      double m = ( e.flops() * (double)freq / (Stat::evaluate(c) * 1000000000. ));
      details::measures_map[details::identify_result(name,e,*this)] = m;
      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "GFLOPS" + Stat::unit();
    }
  };
} }

#endif
