//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_LOGPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_LOGPI_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Logpi generic tag

     Represents the Logpi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Logpi, double, 1
                                , 0x3f928682LL, 0x3ff250d048e7a1bdULL //1.1447298858494001741434273513531
                                );
  }
  /*!
    Generates value \f$\log\pi\f$

    @par Semantic:

    @code
    T r = Logpi<T>();
    @endcode

    is similar to:

    @code
    T r = log(sqrt(Pi<T>());
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Logpi, Logpi)
} }

#include <boost/simd/constant/common.hpp>

#endif
