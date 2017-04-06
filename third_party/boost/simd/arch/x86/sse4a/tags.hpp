//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4A_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4A_TAGS_HPP_INCLUDED

#include <boost/simd/arch/x86/ssse3/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief AMD SSE 4A SIMD architecture hierarchy tag

    This tag represent architectures implementing the AMD SSE 4A SIMD instructions set.
  **/
  struct sse4a_
  {
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::sse4a_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =  detect_feature(6, 0x80000001, detail::ecx);
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
    Global object for accessing SSE4a support informations
  **/
  static detail::support<sse4a_> const sse4a = {};
} }

#endif
