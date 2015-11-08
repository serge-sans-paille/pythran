//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_SQRT_2OPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_SQRT_2OPI_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Sqrt_2opi generic tag

     Represents the Sqrt_2opi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2opi, double
                                , 0, 0x3f4c422a
                                , 0x3fe9884533d43651ll
                                )
  }
  /*!
    Constant  \f$\frac{\sqrt2}{\pi}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Sqrt_2opi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = sqrt(Two<T0>())/Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Sqrt_2opi, Sqrt_2opi);
}

#endif

