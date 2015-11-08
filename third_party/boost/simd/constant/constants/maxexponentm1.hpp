//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENTM1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXEXPONENTM1_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxexponentm1 generic tag

     Represents the Maxexponentm1 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxexponentm1 : ext::pure_constant_<Maxexponentm1>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxexponentm1> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c<typename Target::type,0> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponentm1::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,126> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Maxexponentm1::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,1022> {};

  }
  /*!
    Generates the maximum exposant of floating point numbers minus one

    @par Semantic:

    @code
    as_integer<T> r = Maxexponentm1<T>();
    @endcode

    @code
    if T is double
      r =  1022;
    else if T is float
      r =  126;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxexponentm1, Maxexponentm1)
} }

#include <boost/simd/constant/common.hpp>

#endif
