//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_TAGS_HPP_INCLUDED

#include <boost/simd/arch/x86/sse3/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel Supplemental SSE3 SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel Supplemental SSE3 SIMD instructions set.
  **/
  struct ssse3_ : sse3_
  {
    using parent = sse3_;
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::ssse3_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =  detect_feature(9, 0x00000001, detail::ecx);
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
    Global object for accessing SSSE3 support informations
  **/
  static detail::support<ssse3_> const ssse3 = {};
} }

#endif
