//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_X86_SUPPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_X86_SUPPORT_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions/meta/x86/tags.hpp>
#include <boost/simd/sdk/config/details/registration.hpp>
#include <boost/simd/sdk/config/is_supported.hpp>

namespace boost { namespace simd { namespace details
{
  // register detection of X86 extensions
  static support_registration x86_sse ( "sse"
                                      , &boost::simd::is_supported<tag::sse_>
                                      , &registration_list
                                      );
  static support_registration x86_sse2( "sse2"
                                      , &boost::simd::is_supported<tag::sse2_>
                                      , &registration_list
                                      );
  static support_registration x86_sse3( "sse3"
                                      , &boost::simd::is_supported<tag::sse3_>
                                      , &registration_list
                                      );
  static support_registration x86_ssse3 ( "ssse3"
                                        , &boost::simd::is_supported<tag::ssse3_>
                                        , &registration_list
                                        );
  static support_registration x86_sse4a ( "sse4a"
                                        , &boost::simd::is_supported<tag::sse4a_>
                                        , &registration_list
                                        );
  static support_registration x86_sse41 ( "sse4.1"
                                        , &boost::simd::is_supported<tag::sse4_1_>
                                        , &registration_list
                                        );
  static support_registration x86_sse42 ( "sse4.2"
                                        , &boost::simd::is_supported<tag::sse4_2_>
                                        , &registration_list
                                        );
  static support_registration x86_avx ( "avx"
                                      , &boost::simd::is_supported<tag::avx_>
                                      , &registration_list
                                      );
  static support_registration x86_fma4( "fma4"
                                      , &boost::simd::is_supported<tag::fma4_>
                                      , &registration_list
                                      );
  static support_registration x86_xop ( "xop"
                                      , &boost::simd::is_supported<tag::xop_>
                                      , &registration_list
                                      );
  static support_registration x86_fma3( "fma3"
                                      , &boost::simd::is_supported<tag::fma3_>
                                      , &registration_list
                                      );
  static support_registration x86_avx2( "avx2"
                                      , &boost::simd::is_supported<tag::avx2_>
                                      , &registration_list
                                      );
  static support_registration x86_mic ( "mic"
                                      , &boost::simd::is_supported<tag::mic_>
                                      , &registration_list
                                      );
} } }

#endif
