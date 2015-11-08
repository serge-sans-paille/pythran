//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_FPS_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_FPS_HPP_INCLUDED

#include <nt2/sdk/bench/details/compute_stat.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief Frames per second metric

    This metric calculates the FPS of a benchmark.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct fps
  {
    /// @brief Evaluation of the metric in GFLOPS
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , nt2::details::times_set const& t
                      , nt2::details::cycles_set const&
                      ) const
    {
      typedef typename details::compute_state<Stat>::type sc_t;

      double m = e.frame_count() / (sc_t::evaluate(t) * 1e-6);
      details::measures_map[details::identify_result(name,e,*this)] = m;

      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "Frames/s" + Stat::unit();
    }
  };
} }

#endif
