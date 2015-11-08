//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIO_180_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIO_180_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Pio_180 generic tag

     Represents the pio_180 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Pio_180, double
                                , 0, 0x3c8efa35
                                , 0x3f91df46a2529d3all
                                )
  }
  /*!
    Constant \f$\frac\pi{180}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Pio_180<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Pi<T0>()/_180<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio_180, Pio_180);
}

#endif

