//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO_6_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO_6_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief pio_6 generic tag

     Represents the pio_6 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pio_6, double
                                , 0, 0x3f060a92UL
                                , 0x3fe0c152382d7366ULL
                                )
  }
  /*!
    Constant \f$\frac\pi{6}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio_6<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Pi<T0>()/Six<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_6, Pio_6);
}

#endif

