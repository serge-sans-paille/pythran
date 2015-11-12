//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_THREEPIO_4_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_THREEPIO_4_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief threepio_4 generic tag

     Represents the threepio_4 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 8.47842766036889956997e-32
    BOOST_SIMD_CONSTANT_REGISTER( Threepio_4, double
                                , 2, 0x4016cbe4
                                , 0x4002d97c7f3321d2ll
                                )
  }
  /*!
    Constant threepio_4 : \f$3\pi/4\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = threepio_4<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Three<T0>()*Pi<T0>()/Four<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Threepio_4, Threepio_4);
}

#endif

