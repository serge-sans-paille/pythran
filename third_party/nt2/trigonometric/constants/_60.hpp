//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_60_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_60_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief _60 generic tag

     Represents the _60 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _60, double
                                , 60, 0x42700000UL
                                , 0x404e000000000000ULL
                                )
  }
  /*!
    Constant 60.

    @par Semantic:

    For type T0:

    @code
    T0 r = _60<T0>();
    @endcode

    is similar to:

    @code
    T0 r = 60;
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_60, _60);
}

#endif

