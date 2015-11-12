//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MONEO_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MONEO_6_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Moneo_6 generic tag

     Represents the Moneo_6 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Moneo_6, double, 0, 0xBE2AAAAB
                                , 0xBFC5555555555555LL
                                )
  }
  /*!
    Generates value 1/6

    @par Semantic:

    @code
    T r = Moneo_6<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(6);
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Moneo_6, Moneo_6)
} }

#include <boost/simd/constant/common.hpp>

#endif

