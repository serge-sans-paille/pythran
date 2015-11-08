//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_PREPROCESSOR_ONCE_HPP_INCLUDED
#define BOOST_DISPATCH_PREPROCESSOR_ONCE_HPP_INCLUDED

#if defined(_MSC_VER)

#define BOOST_DISPATCH_ONCE                                                    \
__pragma( warning(push) )                                                      \
__pragma( warning(disable:4127) )                                              \
while( 0 )                                                                     \
__pragma( warning(pop) )                                                       \
/**/

#else
/*!
  @brief Warning-free do { ... } while(0) helper

  MSVC emits a spurious warning about the classical do ... while(0)
  hygienic macro due to a compiler bug. As the warning, in other context
  and on other compiler, is useful, this macro helps wrapping the @c while(0)
  in a warning-safe construct.

  Original implementation was found on:
  http://stackoverflow.com/questions/1946445/c-c-how-to-use-the-do-while0-construct-without-compiler-warnings-like-c412
**/
#define BOOST_DISPATCH_ONCE while( 0 )

#endif

#endif
