//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO2_3T_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO2_3T_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio2_3t generic tag

     Represents the Pio2_3t constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 8.47842766036889956997e-32
    BOOST_SIMD_CONSTANT_REGISTER( Pio2_3t, double
                                , 0, 0x248d3132
                                , 0x397B839A252049C1ll
                                )
  }
  /*!
    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio2_3t<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio2_3t, Pio2_3t);
}

#endif

