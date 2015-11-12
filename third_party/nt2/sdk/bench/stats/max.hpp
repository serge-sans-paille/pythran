//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_STATS_MAX_HPP_INCLUDED
#define NT2_SDK_BENCH_STATS_MAX_HPP_INCLUDED

#include <boost/accumulators/statistics/max.hpp>
#include <string>

namespace nt2 { namespace bench { namespace stats
{
  /*!
    @brief Maximum statistics

    Used as a Metric parameter, max_ make the metric computes the
    maximum value of its samples
  **/
  struct max_
  {
    /// @brief Samples processing function
    template<typename Samples> static inline double evaluate(Samples const& d)
    {
      return boost::accumulators::max(d);
    }

    /// @brief Statistics display
    static std::string unit() { return " (max)"; }
  };
} } }

#endif
