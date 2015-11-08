//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_180_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_180_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief _180 generic tag

     Represents the _180 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _180, double
                                , 180, 0x43340000
                                , 0x4066800000000000ll
                                )
  }

  /*!
    Constant 180.

    @par Semantic:

    For type T0:

    @code
    T0 r = _180<T0>();
    @endcode

    is similar to:

    @code
    T0 r = 180;
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_180, _180);
}

#endif

