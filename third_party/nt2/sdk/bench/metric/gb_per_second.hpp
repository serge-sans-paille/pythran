//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_GB_PER_SECOND_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_GB_PER_SECOND_HPP_INCLUDED

#include <nt2/sdk/bench/details/compute_stat.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief Gigabytes per second metric

    This metric extracts bandwidth based information from a
    set of timing samples and returns a measure in Gb/s.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct gb_per_second
  {
    /*!
      Construct a gb_per_second metric object by specifying the amount of
      data movement per byte processed.

      @param t Number of memory transfer per bytes
    **/
    gb_per_second(std::size_t t = 1) : transfer_(t) {}

    /// @brief Evaluation of the metric in Gb/s
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , nt2::details::times_set const& t
                      , nt2::details::cycles_set const&
                      ) const
    {
      typedef typename details::compute_state<Stat>::type sc_t;
      double gb = static_cast<double>(1L<<30);
      double m = (e.size()*transfer_ / (sc_t::evaluate(t) * 1e-6 ))/gb;
      details::measures_map[details::identify_result(name,e,*this)] = m;
      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "GB/s" + Stat::unit();
    }

    private:
    std::size_t transfer_;
  };
} }

#endif


