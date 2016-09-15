//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_ENFORCE_PRECISION_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_ENFORCE_PRECISION_HPP_INCLUDED
#include <boost/predef.h>
#include <boost/core/ignore_unused.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <float.h>

namespace boost { namespace simd { namespace detail
{
  #ifdef BOOST_ARCH_X86_AVAILABLE
  namespace x86
  {
    template<class T>
    struct x87_precision_flag;

    template<>
    struct x87_precision_flag<float>
    {
      static const unsigned short value = 0;
    };

    template<>
    struct x87_precision_flag<double>
    {
      static const unsigned short value = 2;
    };

    template<>
    struct x87_precision_flag<long double>
    {
      static const unsigned short value = 1;
    };

    BOOST_FORCEINLINE unsigned short x87_get_control_word()
    {
    #ifdef _MSC_VER
      #ifndef BOOST_ARCH_X86_64_AVAILABLE
      unsigned short cw;
      __asm {
        fnstcw cw
      }
      return cw;
      #else
      // FIXME: MSVC x64 doesn't support inline ASM
      return 0;
      #endif
    #elif defined(__GNUC__)
      unsigned short cw;
      __asm__ __volatile__ ("fnstcw %w0" : "=m" (cw));
      return cw;
    #else
      #error unsupported compiler to manage x87 floating-point control word
    #endif
    }

    BOOST_FORCEINLINE void x87_set_control_word(unsigned short cw)
    {
    #ifdef _MSC_VER
      #ifndef BOOST_ARCH_X86_64_AVAILABLE
      __asm {
        fldcw cw
      }
      #else
      // FIXME: MSVC x64 doesn't support inline ASM
      boost::ignore_unused(cw);
      #endif
    #elif defined(__GNUC__)
      __asm__ __volatile__ ("fldcw %0" : : "m" (cw));
    #else
      #error unsupported compiler to manage x87 floating-point control word
    #endif
    }
  }
  #endif

  template<class T, class Enable = void>
  struct enforce_precision
  {
    BOOST_FORCEINLINE enforce_precision()
    {
    }
  };

  #if !defined(FLT_EVAL_METHOD) && defined(__FLT_EVAL_METHOD__)
  #define FLT_EVAL_METHOD __FLT_EVAL_METHOD__
  #endif

  #ifdef FLT_EVAL_METHOD
    #if FLT_EVAL_METHOD != 0
      #ifndef BOOST_SIMD_HAS_X87
        #define BOOST_SIMD_HAS_X87
      #endif
    #endif

  // default without FLT_EVAL_METHOD is to have x87 in 32-bit and no x87 in 64-bit
  // can force otherwise with BOOST_SIMD_NO_X87
  #elif defined(BOOST_ARCH_X86_AVAILABLE) && !defined(BOOST_ARCH_X86_64_AVAILABLE) && !defined(BOOST_SIMD_NO_X87)
    #ifndef BOOST_SIMD_HAS_X87
      #define BOOST_SIMD_HAS_X87
    #endif
  #endif

  #ifdef BOOST_SIMD_HAS_X87
  template<class T>
  struct enforce_precision<T, typename boost::enable_if< boost::is_floating_point<T> >::type>
  {
    BOOST_FORCEINLINE enforce_precision() : cw(x86::x87_get_control_word())
    {
      unsigned short new_cw = (cw & 0xFCFF) | (x86::x87_precision_flag<T>::value << 8);
      x86::x87_set_control_word(new_cw);
    }

    BOOST_FORCEINLINE ~enforce_precision()
    {
      x86::x87_set_control_word(cw);
    }

    unsigned short cw;
  };
  #endif
} } }

#endif
