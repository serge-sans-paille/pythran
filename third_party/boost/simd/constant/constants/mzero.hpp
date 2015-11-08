//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MZERO_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mzero generic tag

     Represents the Mzero constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Mzero, double, 0
                                , 0x80000000, 0x8000000000000000ULL
                                )
  }
  /*!
    Generates value -0

    @par Semantic:

    @code
    T r = Mzero<T>();
    @endcode

    is similar to:

    @code
    T r = -T(0);
    @endcode

    @ par Note:

    This is a special constant as it can be used and considered
    identical to zero, except that for floating point numbers,
    there is two different representation of zero with different bit of sign.

    The existence of the sign can be used in special circumstances as
    choosing between \f$+\infty\f$ and \f$-\infty\f$ instead of nan in computing 1/0.
    \par

    The sign of zero can be accessed through the @c is_negative
    and @c is_positive predicates or the @funcref{boost::simd::bitofsign} function.
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mzero, Mzero)
} }

#include <boost/simd/constant/common.hpp>

#endif
