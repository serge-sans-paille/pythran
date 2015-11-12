//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_RADINDEGR_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_RADINDEGR_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Radindegr generic tag

     Represents the Radindegr constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Radindegr, double
                                , 0, 0xb53387c1
                                , 0xbce1e7ab456405f8ull
                                )
  }
  /*!
    Constant Radian in Degree residue can help to obtain better conversion
    from Radian to Degree

    @par Semantic:

    For type T0:

    @code
    T0 r = Radindegr<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Radindegr, Radindegr);
}

#endif

