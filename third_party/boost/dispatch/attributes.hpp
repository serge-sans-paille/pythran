//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED
#define BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED

/*!
  @file
  @brief Defines wrapper for compiler dependent attributes

  Variables and functions attributes provided by some compilers allow for
  valuable additional optimizations. This file provide portable macro to
  benefit from such attributes.
**/

#include <boost/config.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

#if defined(DOXYGEN_ONLY)
/*!
  @brief Mark a function as candidate for no inlining

  This macro expands to a potential compiler specific function attribute hinting
  the compiler to not inline it.

  @par Usage:

  @code
  BOOST_DISPATCH_NOINLINE void foo()
  {
    // ...
  }
  @endcode

**/
#define BOOST_DISPATCH_NOINLINE

/*!
  @brief Mark a function as deprecated

  This macro expands to a compiler specific function attribute emitting a
  warning indicating said function is deprecated.

  @par Usage:

  @code
  BOOST_DISPATCH_DEPRECATED void foo()
  {
    // ...
  }
  @endcode

**/
 #define BOOST_DISPATCH_DEPRECATED

/*!
  @brief Mark a pointer or reference as restricted

  This macro expands to a potential compiler specific parameters attribute
  indicating that a given pointer or reference is not aliasing any other pointer
  or reference.

  @par Usage:

  @code
  void* BOOST_DISPATCH_RESTRICT ptr = malloc(1337);
  @endcode

  @see BOOST_DISPATCH_NO_RESTRICT_REFERENCES
**/
#define BOOST_DISPATCH_RESTRICT

/*!
  @brief Mark a pointer or reference as restricted

  If BOOST_DISPATCH_NO_RESTRICT_REFERENCES is defined, current compiler does not
  support restricted reference. Using BOOST_DISPATCH_RESTRICT on references
  requires checking for this flag.

  @see BOOST_DISPATCH_RESTRICT
**/
#define BOOST_DISPATCH_NO_RESTRICT_REFERENCES

/*!
  @brief Mark a function as non-throwing

  This macro expands to a compiler specific function attribute indicating that
  said function can not throw any kind of exceptions.

  @par Usage:

  @code
  void foo() BOOST_DISPATCH_NOTHROW
  {
    // ...
  }
  @endcode

**/
#define BOOST_DISPATCH_NOTHROW

/*!
  @brief DOCTODO

  @par Usage:

  @code
  @endcode

**/
#define BOOST_DISPATCH_OVERRIDE

/*!
  @brief Mark a class as having no VTABLE

  This macro expands to a compiler specific type attribute indicating that
  said class or structure can be optimized by knowing there is no VTABLE
  to be generated for it.

  @par Usage:

  @code
  class foo BOOST_DISPATCH_NOVTABLE
  {
    // ...
  }
  @endcode

**/
#define BOOST_DISPATCH_NOVTABLE

#else

#ifndef BOOST_FORCEINLINE
#  if defined(__GNUC__)
#    define BOOST_FORCEINLINE inline __attribute__((always_inline))
#  elif defined(_MSC_VER)
#     define BOOST_FORCEINLINE __forceinline
#  else
#    define BOOST_FORCEINLINE inline
#  endif
#endif

#ifndef BOOST_LIKELY
#  if defined(__GNUC__)
#    define BOOST_LIKELY(x) __builtin_expect(x, 1)
#  else
#    define BOOST_LIKELY(x) x
#  endif
#endif

#ifndef BOOST_UNLIKELY
#  if defined(__GNUC__)
#    define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#  else
#    define BOOST_UNLIKELY(x) x
#  endif
#endif

// deprecated name
#define BOOST_DISPATCH_FORCE_INLINE BOOST_FORCEINLINE

#if defined(__GNUC__)
#define BOOST_DISPATCH_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_NOINLINE __declspec(noinline)
#else
#define BOOST_DISPATCH_NOINLINE
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_DEPRECATED __declspec(deprecated)
#else
#define BOOST_DISPATCH_DEPRECATED
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_RESTRICT __restrict__
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_RESTRICT __restrict
#else
#define BOOST_DISPATCH_RESTRICT
#endif
#if BOOST_PP_IS_EMPTY(BOOST_DISPATCH_RESTRICT)
#define BOOST_DISPATCH_NO_RESTRICT
#endif

#if defined(BOOST_DISPATCH_NO_RESTRICT) || defined(_MSC_VER)
#define BOOST_DISPATCH_NO_RESTRICT_REFERENCES
#endif

#if defined(_MSC_VER)
#define BOOST_DISPATCH_NOTHROW  __declspec( nothrow )
#elif defined(__GNUC__)
#define BOOST_DISPATCH_NOTHROW __attribute__(( nothrow ))
#else
#define BOOST_DISPATCH_NOTHROW
#endif

#if defined(_MSC_VER)
#define BOOST_DISPATCH_OVERRIDE override
#elif defined(__GNUC__)
#define BOOST_DISPATCH_OVERRIDE
#else
#define BOOST_DISPATCH_OVERRIDE
#endif

#if defined(_MSC_VER)
#define BOOST_DISPATCH_NOVTABLE __declspec( novtable )
#else
#define BOOST_DISPATCH_NOVTABLE
#endif

#endif

#endif
