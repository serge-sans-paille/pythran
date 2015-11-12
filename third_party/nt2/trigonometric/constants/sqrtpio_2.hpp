//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_SQRTPIO_2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_SQRTPIO_2_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Sqrtpio_2 generic tag

     Represents the Sqrtpio_2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrtpio_2, double
                                , 0, 0x3f62dfc5
                                , 0x3fec5bf891b4ef6bll
                                )
  }
  /*!
    Constant Sqrtpio_2 : \f$\frac{\sqrt2}{\pi}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = sqrtpio_2<T0>();
    @endcode

    is similar to:

    @code
    T0 r = sqrt(Two<T0>())/Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Sqrtpio_2, Sqrtpio_2);//0.88622692545275801364908374167057
}

#endif

