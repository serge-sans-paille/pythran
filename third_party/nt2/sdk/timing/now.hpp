//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_NOW_HPP_INCLUDED
#define NT2_SDK_TIMING_NOW_HPP_INCLUDED

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/timing/config.hpp>

#include <boost/noncopyable.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace nt2
{
  typedef nt2::uint64_t cycles_t;
  typedef nt2::uint64_t time_quantum_t;
  typedef double        seconds_t;
  typedef double        microseconds_t;

  BOOST_DISPATCH_NOTHROW cycles_t       read_cycles();

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOTHROW time_quantum_t time_quantum();

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOTHROW seconds_t      now();

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOTHROW unsigned long  get_cpu_freq();

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOTHROW microseconds_t to_microseconds( time_quantum_t );

  NT2_SDK_TIMING_DECL
  BOOST_DISPATCH_NOTHROW time_quantum_t to_timequantums( microseconds_t );
}

#include <nt2/sdk/timing/details/cycles.hpp>

#endif
