//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_BITINCREMENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_BITINCREMENT_HPP_INCLUDED

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
      @brief Bitincrement generic tag

      Represents the Bitincrement constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct Bitincrement : ext::pure_constant_<Bitincrement>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Bitincrement> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct apply : meta::int_c<typename Target::type,1> {};
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Bitincrement::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<1> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Bitincrement::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<1> {};
  }

  /*!
    Generates a value in the chosen type all bits of which are set to 1.

    @par Semantic:

    @code
    T r = Bitincrement<T>();
    @endcode

    is similar to

    @code
    if NO_DENORMALS
      r =  Smallestpositivevalue<T>();
    else
      r =  minDenormal<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION( boost::simd::tag::Bitincrement, Bitincrement)
} }

#include <boost/simd/constant/common.hpp>

#endif
