//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_TAGS_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>
#include <boost/simd/arch/x86/ssse3/tags.hpp>
#include <boost/simd/arch/x86/sse4a/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel SSE 4.1 SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel SSE 4.1 SIMD instructions set.
  **/
  struct  sse4_1_ : ssse3_
  {
    using parent = ssse3_;
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::sse4_1_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =  detect_feature(19, 0x00000001, detail::ecx);
        #else
        support_ =  false;
        #endif
      }

      inline bool is_supported() const { return support_; }

      private:
      bool support_;
    };
  }

  /*!
    @ingroup  group-api
    Global object for accessing SSE4.1 support informations
  **/
  static detail::support<sse4_1_> const sse4_1 = {};
} }

#endif
