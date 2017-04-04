//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_2_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_2_TAGS_HPP_INCLUDED

#include <boost/simd/arch/x86/sse4_1/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel SSE 4.2 SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel SSE 4.2 SIMD instructions set.
  **/
  struct sse4_2_  : sse4_1_
  {
    using parent = sse4_1_;
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::sse4_2_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =  detect_feature(20, 0x00000001, detail::ecx);
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
    Global object for accessing SSE4.2 support informations
  **/
  static detail::support<sse4_2_> const sse4_2 = {};
} }

#endif
