//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_SPEEDUP_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_SPEEDUP_HPP_INCLUDED

#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <string>
#include <map>
#include <iostream>

namespace nt2 { namespace details
{
  // This string to string map contains unabridged results for each benchmarks.
  extern NT2_TEST_BENCHMARK_DECL std::map<std::string, double> measures_map;
} }

namespace nt2 { namespace bench
{
  /*!
    @brief Relative speed-up metric

    This metric computes the speed-up between the current experiment results
    and a reference experiment results referenced by its registered name and
    the Metric passed as a template parameter.

    @tparam Experiment  Reference experiment to compare to
    @tparam Metric      Reference metric to retrieve
  **/
  template<typename Experiment, typename Metric>
  struct speedup
  {
    /// @brief Default constructor
    speedup () : exp_id( nt2::type_id<Experiment>() ) {}

    /// @brief Evaluation of the metric in CPU cycles
    template<typename XP> inline
    double operator() ( XP const& e
                      , std::string const& name
                      , details::times_set const&, details::cycles_set const&
                      ) const
    {
      double o = details::measures_map[details::identify_result(exp_id,e,stat_)];
      double n = details::measures_map[details::identify_result(name,e,stat_)];

      return o/n;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "x faster than " + exp_id + " " + stat_.unit();
    }

    private:
    std::string exp_id;
    Metric      stat_;
  };
} }

#endif
