//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_FOUROPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_FOUROPI_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Fouropi generic tag

     Represents the Fouropi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fouropi, double
                                , 1, 0x3fa2f983
                                , 0x3ff45f306dc9c883ll
                                )
  }
  /*!
    Constant \f$\frac4\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Fouropi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Four<T0>()/Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Fouropi, Fouropi);
}

#endif

