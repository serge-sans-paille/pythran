//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_2OSQRTPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_2OSQRTPI_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief _2osqrtpi generic tag

     Represents the _2osqrtpi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _2osqrtpi, double
                                , 0, 0x3ecc422a
                                , 0x3fd9884533d43651ll
                                )
  }
  /*!
    Constant _2osqrtpi : \f$\frac{2}{\sqrt\pi}\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = _2osqrtpi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Two<T0>()/sqrt(Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_2osqrtpi, _2osqrtpi);//1.1283791670955125738961589031215

}

#endif

