//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_TWOPIO_3_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_TWOPIO_3_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Twopio_3 generic tag

     Represents the Twopio_3 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twopio_3, double
                                , 0, 0x40060a92LL
                                , 0x4000c152382d7366ULL
                                )
  }
  /*!
    Constant \f$2\frac\pi{3}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Twopio_3<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Two<T0>()*Pi<T0>()/Three<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Twopio_3, Twopio_3);
}

#endif

