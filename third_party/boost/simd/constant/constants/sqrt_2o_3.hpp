//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRT_2O_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRT_2O_3_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Sqrt_2o_3 generic tag

     Represents the Sqrt_2o_3 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Sqrt_2o_3, double, 0
                                , 0x3f5105ec, 0x3fea20bd700c2c3ell
                                )
  }

  /*!
    Generates value \f$\frac{\sqrt2}3\f$

    @par Semantic:

    @code
    T r = Sqrt_2o_3<T>();
    @endcode

    is similar to:

    @code
    T r = T(sqrt(as_floating<T>(2)))/T(3);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrt_2o_3, Sqrt_2o_3)
} }

#include <boost/simd/constant/common.hpp>

#endif
