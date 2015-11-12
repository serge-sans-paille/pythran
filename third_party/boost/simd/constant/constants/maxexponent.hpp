//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxexponent generic tag

     Represents the Maxexponent constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxexponent : ext::pure_constant_<Maxexponent>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxexponent> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponent::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,127> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponent::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,1023> {};

  }
  /*!
    Generates the maximum exposant of floating point numbers

    @par Semantic:

    @code
    as_integer<T> r = Maxexponent<T>();
    @endcode

    @code
    if T is double
      r =  1023;
    else if T is float
      r =  127;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxexponent, Maxexponent)
} }

#include <boost/simd/constant/common.hpp>

#endif
