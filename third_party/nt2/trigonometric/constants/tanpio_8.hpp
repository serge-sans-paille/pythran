//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_TANPIO_8_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_TANPIO_8_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Tanpio_8 generic tag

     Represents the Tanpio_8 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Tanpio_8, double
                                , 0, 0x3ed413cdUL
                                , 0x3fda827999fcef31ULL
                                )
  }
  /*!
    Constant \f$\tan3\frac\pi{8} = \sqrt2 - 1\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Tanpio_8<T0>();
    @endcode

    is similar to:

    @code
    T0 r = sqrt(2.0)-1.0;
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Tanpio_8, Tanpio_8);
}

#endif

