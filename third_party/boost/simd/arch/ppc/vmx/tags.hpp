//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_TAGS_HPP_INCLUDED

#include <boost/simd/arch/common/tags.hpp>
#include <boost/simd/detail/support.hpp>
#include <boost/predef/architecture.h>
#include <boost/predef/os.h>

#if BOOST_ARCH_PPC
  #if BOOST_OS_MACOS
    #include <Gestalt.h>
  #else
    #include <boost/simd/detail/auxv.hpp>
    #include <asm/cputable.h>
  #endif
#endif

namespace boost { namespace simd
{
  /*!
    @ingroup group-hierarchy
    @brief PowerPC VMX SIMD architecture hierarchy tag

    This tag represent architectures implementing the VMX SIMD instructions set.
  **/
  struct vmx_ : simd_
  {
    using parent = simd_;
  };

  namespace detail
  {
    template<> struct support<::boost::simd::vmx_>
    {
      support()
      {
        #if BOOST_ARCH_PPC
          #if BOOST_OS_MACOS
            long cpuAttributes;
            support_ = false;
            OSErr err = Gestalt( gestaltPowerPCProcessorFeatures, &cpuAttributes );
            if( noErr == err )
            {
              support_ = ( 1 << gestaltPowerPCHasVectorInstructions) & cpuAttributes;
            }
          #else
            support_ = detail::hwcap() & PPC_FEATURE_HAS_ALTIVEC;
          #endif
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
    Global object for accessing VMX support informations
  **/
  static detail::support<vmx_> const vmx = {};
} }

#endif
