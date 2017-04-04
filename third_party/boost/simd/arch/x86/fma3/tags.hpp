//==================================================================================================
/*!
  @file

  Aggregates SIMD extension tags for Intel X86 and AMD

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_FMA3_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_FMA3_TAGS_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/simd/detail/cpuid.hpp>

namespace boost { namespace simd
{
  struct fma3_
  {
  };

  namespace detail
  {
    template<> struct support< ::boost::simd::fma3_>
    {
      support()
      {
        #if BOOST_ARCH_X86
        support_ =   detect_feature(12, 0x00000001, detail::ecx)
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
    Global object for accessing FMA3 support informations
  **/
  static detail::support<fma3_> const fma3 = {};
} }

#endif
