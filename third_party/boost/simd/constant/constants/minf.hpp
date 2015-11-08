//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/config.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Minf generic tag

     Represents the Minf constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Valmin;

    struct Minf : ext::pure_constant_<Minf>
    {
      typedef double                    default_type;
      typedef ext::pure_constant_<Minf> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct apply : meta::make_dependent<Valmin, Dummy>::type::template apply<Target,Dummy> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Minf::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0xFF800000> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Minf::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0xFFF0000000000000ULL> {};
  }
  /*!
    Generates  -inf IEEE value (\f$ - \infty \f$) for floating types and minimum value
    for integer types

    @par Semantic:

    @code
    T r = Minf<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = Valmin<T>()
    else if T is floating
      r =  IEEE -inf value;
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Minf, Minf)
} }

#include <boost/simd/constant/include/constants/valmin.hpp>
#include <boost/simd/constant/common.hpp>

#endif
