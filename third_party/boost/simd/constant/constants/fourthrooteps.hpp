//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FOURTHROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FOURTHROOTEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fourthrooteps generic tag

     Represents the Fourthrooteps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fourthrooteps,double,1
                                , 0x3C9837F0,0x3F20000000000000ULL
                                )
  }
  /*!
    Generates the 4th root of constant @c Eps.

    @par Semantic:

    @code
    T r = Fourthrooteps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(1)
    else if T is double
      r =  pow(2.0, -13);
    else if T is float
      r =  pow(2.0f, -5.75f);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fourthrooteps, Fourthrooteps)
} }

#include <boost/simd/constant/common.hpp>

#endif
