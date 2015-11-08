//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_INF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_INF_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/config.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Inf generic tag

     Represents the Inf constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Valmax;

    struct Inf : ext::pure_constant_<Inf>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Inf> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct apply : meta::make_dependent<Valmax, Dummy>::type::template apply<Target,Dummy> {};
    };


    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Inf::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x7F800000> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Inf::apply<boost::dispatch::meta::double_<T>,Dummy>
      : meta::double_<0x7FF0000000000000ULL> {};
  }

  /*!
    Generates the Inf IEEE value (\f$\infty\f$) for floating types and maximum value
    for integer types

    @par Semantic:

    @code
    T r = Inf<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = Valmax<T>()
    else if T is floating
      r =  IEEE inf value;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Inf, Inf)

} }

#include <boost/simd/constant/include/constants/valmax.hpp>
#include <boost/simd/constant/common.hpp>

#endif
