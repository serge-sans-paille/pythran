//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_REGION_HPP_INCLUDED
#define BOOST_SIMD_META_REGION_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Static definition of region of interest

    Defines a compile-time region of interest as a series of 1D or 2D offsets
    around a central value.

    @tparam I0 .
    @tparam I1 .
    @tparam J0 .
    @tparam J1 .
  **/
  template<int I0, int I1, int J0 = 0, int J1 = 0>
  struct region_
  {
    // Region corners
    static const int w_min    = I0;
    static const int w_max    = I1;
    static const int h_min    = J0;
    static const int h_max    = J1;

    // Region metric
    static const int width    = I1 - I0 + 1;
    static const int height   = J1 - J0 + 1;
    static const int surface  = width*height;
    static const int ndims    = height ? 2 : 1;
  };

  template<int I0, int I1> BOOST_FORCEINLINE region_<I0,I1> around()
  {
    return region_<I0,I1>();
  }
} }

#endif
