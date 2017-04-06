//==================================================================================================
/*!
  @file

  Useful tags forward declarations and aliases

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_TAGS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_TAGS_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace tag
{
  namespace tt = nsm::type_traits;

  struct exp_;
  struct exp2_;
  struct exp10_;
  struct log_;
  struct log2_;
  struct log10_;

  using not_simd_type = tt::integral_constant<bool, false>;
  using simd_type = tt::integral_constant<bool, true>;

  struct restricted {};
  struct regular {};

  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag {};
  struct degree_tag {};
  struct pi_tag     {};
  enum reduction
  {
    r_0_pio4, r_0_pio2, r_0_20pi, r_0_mpi, r_0_dmpi, r_0_inf
  };

  struct very_small_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio4;
  };

  const very_small_tag very_small_ = {};

  struct straight_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio2;
  };

  const straight_tag straight_ = {};

  struct small_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_20pi;
  };

  const small_tag small_ = {};

  struct medium_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_mpi;
  };

  const medium_tag medium_ = {};

  struct big_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_inf;
  };

  const big_tag big_ = {};

  struct direct_small_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_20pi;
    static const reduction range = r_0_20pi;
  };

  const direct_small_tag direct_small_ = {};

  struct direct_medium_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_mpi;
    static const reduction range = r_0_mpi;
  };

  const direct_medium_tag direct_medium_ = {};

  struct direct_big_tag
  {
    using type = tag::regular;
    static const bool clipped =  false;
    static const reduction start = r_0_inf;
    static const reduction range = r_0_inf;
  };

  const direct_big_tag direct_big_ = {};

  struct clipped_pio4_tag
  {
    using parent = clipped_pio4_tag;
    using hierarchy_tag = void;
    using type = tag::restricted;
    static const bool clipped =  true;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio4;
  };

  const clipped_pio4_tag clipped_pio4_ = {};
  const clipped_pio4_tag clipped_45d_  = {};
  const clipped_pio4_tag clipped_quarter_= {};
  const clipped_pio4_tag clipped_very_small_= {};

  struct clipped_small_tag
  {
    using type = tag::regular;
    static const bool clipped =  true;
    static const reduction start = r_0_20pi;
    static const reduction range = r_0_20pi;
  };

  const clipped_small_tag clipped_small_ = {};

  struct clipped_medium_tag
  {
    using type = tag::regular;
    static const bool clipped =  true;
    static const reduction start = r_0_mpi;
    static const reduction range = r_0_mpi;
  };

  const clipped_medium_tag clipped_medium_ = {};


} } }

#endif
