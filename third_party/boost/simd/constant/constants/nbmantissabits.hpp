//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_NBMANTISSABITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_NBMANTISSABITS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Nbmantissabits generic tag

     Represents the Nbmantissabits constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Nbmantissabits : ext::pure_constant_<Nbmantissabits>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Nbmantissabits> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply : meta::int_c < typename Target::type
                                  , sizeof(typename Target::type)*CHAR_BIT
                                  >
      {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Nbmantissabits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::int_c<boost::simd::int32_t,23> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Nbmantissabits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::int_c<boost::simd::int64_t,52> {};
  }
  /*!
    Constant Nbmantissabits, The number of mantissa bits of a floating point number.

    @par Semantic:

    @code
    T r = Nbmantissabits<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = sizeof(T)*8
    else if T is double
      r =  52;
    else if is float
      r =  23;
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nbmantissabits, Nbmantissabits)
} }

#include <boost/simd/constant/common.hpp>

#endif
