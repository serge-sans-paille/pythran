//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRT_1O_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRT_1O_5_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sqrt_1o_5 generic tag

     Represents the Sqrt_1o_5 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_1o_5, double, 0
                                , 0x3ee4f92e, 0x3fdc9f25c5bfedd9ll
                                )
  }

  /*!
    Generates value \f$ \sqrt{\frac15}\f$

    @par Semantic:

    @code
    T r = Sqrt_1o_5<T>();
    @endcode

    is similar to:

    @code
    T r = sqrt(T(1)/T(5));
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrt_1o_5, Sqrt_1o_5)
} }

#include <boost/simd/constant/common.hpp>

#endif
