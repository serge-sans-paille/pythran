//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_EULER_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_EULER_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Euler generic tag

     Represents the Eps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Euler, double
                                , 0, 0x3f13c468
                                , 0x3fe2788cfc6fb619ll
                                )
  }
  /*!
    GeneratesEuler constant.

    @par Semantic:
    The Euler constant can be defined as \f$\displaystyle \lim_{n \rightarrow \infty} \left(\sum_1^n \frac1n -\log n\right)\f$

    @code
    T r = Euler<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.577215664901532860606512090082402431042159335939923598805767234884867726777664670936947063291746749);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Euler, Euler);
}

#endif
