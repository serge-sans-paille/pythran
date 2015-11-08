//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_EXPNIBIG_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_EXPNIBIG_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Expnibig generic tag

      Represents the Expnibig constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Expnibig, double
                                , 0, 0x4b800000         // 2^24
                                , 0x4380000000000000ll  // 2^57
                                )
  }
  /*!
    Generates a constant used in expni.

    @par Semantic:

    @code
    T r = Expnibig<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(0)
    else if T is double
      r =  pow(2.0, 57);
    else if T is float
      r =  pow(2.0f, 24);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Expnibig, Expnibig);
}

#endif
