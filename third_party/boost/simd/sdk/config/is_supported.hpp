//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_IS_SUPPORTED_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_IS_SUPPORTED_HPP_INCLUDED

/*!
 *\file is_supported.hpp
 * \brief Runtime function returning the SIMD extension supported.
 * For detecting a new extenion from a new vendor you need to add a
 * vendor case and provide the right specialization of cpuid_mask.
*/
#include <boost/simd/sdk/config/details/detect.hpp>
#include <boost/simd/sdk/config/details/registration.hpp>
#include <string.h>

namespace boost { namespace simd
{
  template<class Tag> inline bool is_supported()
  {
    Tag tag_;
    return config::details::detect(tag_);
  }

  inline int is_supported(const char* name)
  {
    int result = 0;
    details::support_registration* c = details::registration_list.next;

    while(c && result != 1)
    {
      if(strcmp(name,c->name) == 0) result = c->function() ? 1 : -1;
      c = c->next;
    }

    return result;
  }
} }

#include <boost/simd/sdk/config/details/support.hpp>

#endif
