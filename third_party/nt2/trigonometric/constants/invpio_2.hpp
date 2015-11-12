//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_INVPIO_2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_INVPIO_2_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Invpio_2 generic tag

     Represents the invpio_2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    // 6.36619772367581382433e-01
    BOOST_SIMD_CONSTANT_REGISTER( Invpio_2, double
                                , 0, 0x3f22f984
                                , 0x3FE45F306DC9C883ll
                                )
  }
  /*!
    Constant  \f$\frac2\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Invpio_2<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Two<T0>()/Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invpio_2, Invpio_2);
}

#endif

