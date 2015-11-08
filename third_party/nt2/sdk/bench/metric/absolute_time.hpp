//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_ABSOLUTE_TIME_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_ABSOLUTE_TIME_HPP_INCLUDED

#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief Absolute time metric

    This metric extract time based informations from a
    set of timing samples and return a measure in second.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct absolute_time
  {
    /// @brief Evaluation of the metric in second
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , details::times_set const& t
                      , details::cycles_set const&
                      ) const
    {
      double m = Stat::evaluate(t) * 1e-6;
      details::measures_map[details::identify_result(name,e,*this)] = m;
      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "s." + Stat::unit();
    }
  };
} }

#endif
