//==================================================================================================
/*!
  @file

  Aggregates SIMD extension tags for Intel X86 and AMD

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_FMA4_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_FMA4_TAGS_HPP_INCLUDED

#include <boost/simd/arch/x86/avx/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief Intel FMA4 SIMD architecture hierarchy tag

    This tag represent architectures implementing the Intel FMA4 SIMD instructions set.
  **/
  struct fma4_
  {
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::fma4_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =   detect_feature(16, 0x80000001, detail::ecx)
                 &&  detect_feature(27, 0x80000001, detail::ecx);
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
    Global object for accessing FMA4 support informations
  **/
  static detail::support<fma4_> const fma4 = {};

} }

#endif
