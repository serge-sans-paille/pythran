//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_DEGINRAD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_DEGINRAD_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Deginrad generic tag

     Represents the Deginrad constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Deginrad, double
                                , 0, 0x3c8efa35
                                , 0x3f91df46a2529d39ll
                                )
  }
  /*!
    Constant radian in Degree multiplier, \f$\frac{180}\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Deginrad<T0>();
    @endcode

    is similar to:

    @code
    T0 r = _180<T0>()/Pi<T0>() ;
    @endcode

    @see  @funcref{inrad}, @funcref{indeg}, @funcref{Radindeg}, @funcref{Radindegr}
    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Deginrad, Deginrad);

}

#endif

