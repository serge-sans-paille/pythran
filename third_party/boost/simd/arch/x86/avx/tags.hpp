//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_TAGS_HPP_INCLUDED

#include <boost/simd/arch/x86/sse4_2/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel AVX SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel AVX SIMD instructions set.
  **/
  struct avx_     : sse4_2_
  {
    using parent = sse4_2_;
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::avx_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =     detect_feature(28, 0x00000001, detail::ecx)
                   &&  detect_feature(27, 0x00000001, detail::ecx);
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
    Global object for accessing AVX support informations
  **/
  static detail::support<avx_> const avx = {};

} }

#endif
