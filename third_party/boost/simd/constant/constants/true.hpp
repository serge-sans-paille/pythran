//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief True generic tag

     Represents the True constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct True : ext::pure_constant_<True>
    {
      typedef logical<double> default_type;
      typedef ext::pure_constant_<True> parent;
    };
  }
  /*!
    Generates the value True as a logical associated to chosen type

    @par Semantic:

    @code
    T r = True<T>();
    @endcode


    is similar to:

    @code
    auto r = logical<T>(true);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::True, True)
} }

#include <boost/simd/constant/common.hpp>

#endif
