//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_90_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_90_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief _90 generic tag

     Represents the _90 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _90, double
                                , 90, 0x42b40000
                                , 0x4056800000000000ll
                                )
  }
  /*!
    Constant 90.

    @par Semantic:

    For type T0:

    @code
    T0 r = _90<T0>();
    @endcode

    is similar to:

    @code
    T0 r = 90;
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_90, _90);
}

#endif

