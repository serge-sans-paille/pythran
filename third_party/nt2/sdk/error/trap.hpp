//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_TRAP_HPP_INCLUDED
#define NT2_SDK_ERROR_TRAP_HPP_INCLUDED

/**
* @file
* @brief Provides portable, conditionnal breakpoint traps
**/

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>

//==============================================================================
// Detects and define how to emit a TRAP signal
//==============================================================================
#if (   defined(_M_IX86) || defined(__i386__)   \
    ||  defined(_M_IA64) || defined(__ia64__)   \
    )                                           \
    &&  defined(__GNUC__)
#define NT2_DEBUG_TRAP()  __asm("int3")
#elif defined(_MSC_VER)
#define NT2_DEBUG_TRAP()  __debugbreak()
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <csignal>
#define NT2_DEBUG_TRAP() ::raise(SIGTRAP)
#else
#define NT2_DEBUG_TRAP()
#endif

namespace nt2
{
  /**
  * @brief Runtime conditionnal breakpoint trap
  *
  * If @c cond evaluates to true, triggers a breakpoint trap.
  *
  * @param cond Conditionnal trigger for the breakpoint trap
  **/
  BOOST_FORCEINLINE void trap(bool cond) { if(!cond) NT2_DEBUG_TRAP(); }

  /**
  * @brief Runtime inconditionnal breakpoint trap
  *
  * Triggers a breakpoint trap.
  **/
  BOOST_FORCEINLINE void trap() { NT2_DEBUG_TRAP(); }

  /**
  * @brief Compile-time conditionnal breakpoint trap
  *
  * If @c Condition::value evaluates true, triggers a breakpoint trap.
  *
  * @tparam Condition Compile-time boolean integral constant
  **/
  template<class Condition>
  BOOST_FORCEINLINE void
  trap( typename boost::enable_if_c<Condition::value>::type* = 0 )
  {
    NT2_DEBUG_TRAP();
  }

  template<class Condition> BOOST_FORCEINLINE
  void trap( typename boost::disable_if_c<Condition::value>::type* = 0 )
  {}
}

#endif
