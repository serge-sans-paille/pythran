//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_LDEXPMASK_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_LDEXPMASK_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Ldexpmask generic tag

     Represents the Ldexpmask constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Ldexpmask : ext::pure_constant_<Ldexpmask>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Ldexpmask> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply :  meta::int_c<typename Target::type,0> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Ldexpmask::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,0x7F800000> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Ldexpmask::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,0x7FF0000000000000ULL> {};
  }
  /*!
    Generates the mask to extract the exponent
    bits of a floating point value

    @par Semantic:

    @code
    T r = Ldexpmask<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Ldexpmask, Ldexpmask)
} }

#include <boost/simd/constant/common.hpp>

#endif
