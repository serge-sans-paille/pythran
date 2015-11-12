//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_CGOLD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_CGOLD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Cgold generic tag

     Represents the Cgold constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER(Cgold,double,0,0x3EC3910D,0x3FD8722191A02D61ULL)
  }
  /*!
    Generates the conjugate golden ration that is\f$\bar\phi = \frac{1-\sqrt5}{2}\f$

    @par Semantic:

    @code
    T r = Cgold<T>();
    @endcode

    is similar to:

    @code
    T r = (1-sqrt(5))/2;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Cgold, Cgold)
} }

#include <boost/simd/constant/common.hpp>

#endif
