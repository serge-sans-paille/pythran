//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_TAGS_HPP_INCLUDED

#include <boost/simd/arch/common/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel SSE SIMD family hierarchy tag

    This tag represent architectures implementing any Intel SSE-x SIMD instructions sets.
  **/
  struct sse_   : simd_native_ { using parent = simd_native_; };

  /*!
    @ingroup group-hierarchy
    @brief Intel SSE1 SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel SSE1 SIMD instructions set.
  **/
  struct sse1_   : simd_native_
  {
    using parent = simd_native_;
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::sse1_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =  detect_feature(25, 0x00000001, detail::edx);
        #else
        support_ = false;
        #endif
      }

      inline bool is_supported() const { return support_; }

      private:
      bool support_;
    };
  }

  /*!
    @ingroup  group-api
    Global object for accessing SSE1 support informations
  **/
  static detail::support<sse1_> const sse1 = {};
} }

#endif
