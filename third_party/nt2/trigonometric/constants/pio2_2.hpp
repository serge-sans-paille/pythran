//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO2_2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO2_2_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio2_2 generic tag

     Represents the Pio2_2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    //6.07710050630396597660e-11
    BOOST_SIMD_CONSTANT_REGISTER( Pio2_2, double
                                , 0, 0x37354400
                                , 0x3DD0B4611A600000ll
                                )
  }
  /*!
    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio2_2<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio2_2, Pio2_2);
}

#endif

