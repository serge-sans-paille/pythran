//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_VALMIN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_VALMIN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4146)
#endif


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Valmin generic tag

     Represents the Valmin constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Valmin : ext::pure_constant_<Valmin>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Valmin> parent;

    /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename Target::type, 0> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0xFF7FFFFFUL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0xFFEFFFFFFFFFFFFFULL> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<T, T(-128)> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<T, T(-32768)> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::int32_<T>,Dummy>
    : meta::int_c < T
                  , T(-boost::simd::uint32_t(2147483648UL))
                  > {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Valmin::apply<boost::dispatch::meta::int64_<T>,Dummy>
      : meta::int_c < T
                    , T(-boost::simd::uint64_t(9223372036854775808ULL))
                    > {};
  }
  /*!
    Generates the least finite value of a type.

    @par Semantic:

    @code
    T r = Valmin<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1 << (sizeof(T)*8-1);
    else if T is double
      r = -1.7976931348623157e+308;
    else if T is float
      r = -3.4028234e+38f;
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Valmin, Valmin)
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
