//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_LINUX_PERF_EVENT_HPP_INCLUDED
#define NT2_SDK_TIMING_LINUX_PERF_EVENT_HPP_INCLUDED

#include <boost/simd/sdk/config/os.hpp>
#ifdef BOOST_SIMD_OS_LINUX

#include <nt2/sdk/timing/config.hpp>

namespace nt2 { namespace linux_
{
  NT2_SDK_TIMING_DECL extern int perf_event_hw_cycles;
} }

#endif
#endif
