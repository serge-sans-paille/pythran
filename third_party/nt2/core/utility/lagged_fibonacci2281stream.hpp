//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_LAGGED_FIBONACCI2281STREAM_HPP_INCLUDED
#define NT2_CORE_UTILITY_LAGGED_FIBONACCI2281STREAM_HPP_INCLUDED

#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/details/rands.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <boost/random/lagged_fibonacci.hpp>

namespace nt2
{
  class lagged_fibonacci2281stream_ : public randstream_
  {
    public:
    NT2_DEFINE_RAND(lagged_fibonacci2281stream_);

    private:
    boost::random::lagged_fibonacci2281 generator_;
  };

  NT2_CORE_RANDOM_DECL nt2::randstream_* lagged_fibonacci2281stream();
}

#endif

