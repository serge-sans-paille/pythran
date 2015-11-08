//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013       MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_EXPERIMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_EXPERIMENT_HPP_INCLUDED

#include <cstddef>
#include <iostream>

namespace nt2 { namespace bench
{
  /*!

  **/
  struct experiment
  {
    void operator()() {}
    std::size_t size() const { return 1u; }
  };

  /*!

  **/
  std::ostream& operator<<(std::ostream& os, experiment const&)
  {
    return os << "n/a";
  }
} }

#endif
