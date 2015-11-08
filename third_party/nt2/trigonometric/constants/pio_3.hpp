//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO_3_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO_3_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief pio_3 generic tag

     Represents the pio_3 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pio_3, double
                                , 0, 0x3f860a92LL
                                , 0x3ff0c152382d7366ULL
                                )
  }
  /*!
    Constant \f$\frac\pi{3}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio_3<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Pi<T0>()/Three<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_3, Pio_3);
}

#endif

