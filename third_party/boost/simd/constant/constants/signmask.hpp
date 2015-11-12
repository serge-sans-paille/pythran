//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SIGNMASK_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SIGNMASK_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Signmask generic tag

     Represents the Signmask constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Signmask : ext::pure_constant_<Signmask>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Signmask> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct apply : meta::int_c<typename Target::type,0> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x80000000UL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x8000000000000000ULL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<T, boost::simd::int8_t(0x80U)> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<T, boost::simd::int16_t(0x8000U)> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::int32_<T>,Dummy>
          : meta::int_c<T, boost::simd::int32_t(0x80000000UL)> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Signmask::apply<boost::dispatch::meta::int64_<T>,Dummy>
          : meta::int_c < T
                        , boost::simd::int64_t(0x8000000000000000ULL)
                        > {};
  }
  /*!
    Generate a mask with the lone most significand bit set to one
    (even if the type is unsigned).

    @par Semantic:

    @code
    T r = Signmask<T>();
    @endcode

    is similar to:

    @code
    T r = bitwise_cast<T>(1 << sizeof(T)*8-1);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Signmask, Signmask)
} }

#include <boost/simd/constant/common.hpp>

#endif
