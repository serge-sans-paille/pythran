//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_20_PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_20_PI_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief _20_pi generic tag

     Represents the _20_pi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _20_pi, double
                                , 63, 0x427b53d1       //20\pi
                                , 0x404f6a7a2955385ell  //20\pi
                                )
  }
  /*!
    Constant \f$20\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = _20_pi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Twenty<T0>()*Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_20_pi, _20_pi);
}

#endif

