//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_VALMAX_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>


#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // cast truncate constants
#endif

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Valmax generic tag

     Represents the Valmax constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Valmax : ext::pure_constant_<Valmax>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Valmax> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply
      {
        // MSVC has some problem parsing this directly as a base class ...
        typedef typename Target::type target_t;
        static const target_t value = ~(typename Target::type
                                        (   typename Target::type(1)
                                          <<  ( sizeof(typename Target::type)
                                              * CHAR_BIT-1
                                              )
                                        )
                                       );

        typedef  meta::int_c < target_t, value> type;
      };
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply< boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x7F7FFFFF> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x7FEFFFFFFFFFFFFFULL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<T, 0xFF> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<T, 0xFFFF> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFUL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmax::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<T, 0xFFFFFFFFFFFFFFFFULL> {};
  }
  /*!
    Generates the greatest finite value of a type.

    @par Semantic:

    @code
    T r = Valmax<T>();
    @endcode

    is similar to:

    @code
    if T is unsigned integral
      r = Allbits<T>();
    if T is signed integral
      r = Allbits<T>()^Signmask<T>();
    else if T is double
      r = 1.7976931348623157e+308
    else if T is float
      r = 3.4028234e+38f
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmax, Valmax)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
