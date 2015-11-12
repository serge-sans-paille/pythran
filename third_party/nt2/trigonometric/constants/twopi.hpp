//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_TWOPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_TWOPI_HPP_INCLUDED
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Twopi generic tag

     Represents the Twopi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Twopi, double
                                , 0, 0x40c90fdb
                                , 0x401921fb54442d18ll
                                )
  }
  /*!
    Constant \f$\frac2\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Twopi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = Two<T0>()*Pi<T0>();
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Twopi, Twopi);
}

#endif

