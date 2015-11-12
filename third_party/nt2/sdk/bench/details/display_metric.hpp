//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_DISPLAY_METRIC_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_DISPLAY_METRIC_HPP_INCLUDED

#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace nt2 { namespace details
{
  extern NT2_TEST_BENCHMARK_DECL std::string current_benchmark;

  /*
    display_metric is a callable object usable with fusion::for_each
    to compute metrics and to display their results
  */
  template<typename Experiment>
  struct display_metric
  {
    display_metric( Experiment const& xp
                  , details::times_set  const& t
                  , details::cycles_set const& c
                  )
          : experiment_(xp), times_(t), cycles_(c)
    {}

    template<typename T> inline void operator()(T& t) const
    {
      std::cout << current_benchmark<< '\t' << experiment_ << '\t'
                << t(experiment_,nt2::type_id(experiment_),times_,cycles_)
                << '\t' << t.unit()
                << '\t' << boost::accumulators::count(times_)
                << std::endl;
    }

    Experiment          const&  experiment_;
    details::times_set  const&  times_;
    details::cycles_set const&  cycles_;

    private:
    display_metric& operator=(display_metric const&);
  };
} }

#endif
