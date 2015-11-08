//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxleftshift generic tag

     Represents the Maxleftshift constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxleftshift : ext::pure_constant_<Maxleftshift>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxleftshift> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename dispatch::meta::
                                     as_integer < typename Target::type
                                                , signed
                                                >::type
                          , sizeof(typename Target::type)*CHAR_BIT-1
                          > {};
    };
  }
  /*!
    Generates the number of bits-1 of the scalar component of the value type

    @par Semantic:

    @code
    as_integer<T> r = Maxleftshift<T>();
    @endcode

    is similar to:

    @code
    as_integer<T> r =size(scalar_of<T>)*8-1;
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxleftshift, Maxleftshift)
} }

#include <boost/simd/constant/common.hpp>

#endif
