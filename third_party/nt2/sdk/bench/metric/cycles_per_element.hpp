//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_CYCLES_PER_ELEMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_CYCLES_PER_ELEMENT_HPP_INCLUDED

#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/args.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief CPU cycles metric

    This metric extract cycles based informations from a
    set of timing samples and return a measure in CPU cycles.

    If no external CPU frequency is provided, cycles_per_element will use
    the direct cycle counter readings for its evaluation. Otherwise, a cycle
    count will be estimated using timing and frequency. In this case, the amount
    of real time spent in each sample must be large enough so that the cycle
    count estimation is numerically valid.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct cycles_per_element
  {
    /// @brief Evaluation of the metric in CPU cycles
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , details::times_set  const& t
                      , details::cycles_set const& c
                      ) const
    {
      double freq = args("frequency",-1);

      double m  = (freq == -1) ? Stat::evaluate(c)/e.size()
                               : (Stat::evaluate(t)*freq)/(e.size()*1e6);

      details::measures_map[details::identify_result(name,e,*this)] = m;
      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "cpe" + Stat::unit();
    }
  };
} }

#endif
