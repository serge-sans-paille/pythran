//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_SELECTION_TAGS_HPP_INCLUDED
#include <nt2/sdk/meta/tags.hpp>

namespace nt2
{
  struct fast       {};
  struct regular    {};

  // tags allowing to choose angle unit in trigonometric functions
  struct radian_tag {};
  struct degree_tag {};
  struct pi_tag     {};

  enum reduction
  {
    r_0_pio4, r_0_pio2, r_0_20pi, r_0_mpi, r_0_dmpi, r_0_inf
  };
  struct very_small_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio4;
  };
  struct straight_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio2;
  };
  struct small_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_20pi;
  };
  struct medium_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_mpi;
  };
  struct big_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_inf;
  };
  struct direct_small_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_20pi;
    static const reduction range = r_0_20pi;
  };
  struct direct_medium_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_mpi;
    static const reduction range = r_0_mpi;
  };
  struct direct_big_
  {
    typedef regular type;
    static const bool clipped =  false;
    static const reduction start = r_0_inf;
    static const reduction range = r_0_inf;
  };
  struct clipped_pio4_
  {
    typedef fast type;
    static const bool clipped =  true;
    static const reduction start = r_0_pio4;
    static const reduction range = r_0_pio4;
  };
  struct clipped_small_
  {
    typedef regular type;
    static const bool clipped =  true;
    static const reduction start = r_0_20pi;
    static const reduction range = r_0_20pi;
  };
  struct clipped_medium_
  {
    typedef regular type;
    static const bool clipped =  true;
    static const reduction start = r_0_mpi;
    static const reduction range = r_0_mpi;
  };
}


#endif
