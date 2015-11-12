//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_REAL_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_REAL_SPLAT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // truncation of constant
#endif

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Real_splat generic tag

     Represents the Real_splat constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    template<boost::simd::uint32_t F,boost::simd::uint64_t D>
    struct Realpattern : ext::pure_constant_< Realpattern<F, D> >
    {
      /// @brief Constant default type
      typedef double default_type;

      /// @brief Parent hierarchy
      typedef ext::pure_constant_< Realpattern<F, D> > parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void> struct apply {};

      /// INTERNAL ONLY
      template<class T,class Dummy>
      struct apply<boost::dispatch::meta::single_<T>,Dummy> : meta::single_<F>
      {};

      /// INTERNAL ONLY
      template<class T, class Dummy>
      struct apply<boost::dispatch::meta::double_<T>,Dummy> : meta::double_<D>
      {};
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D, boost::simd::uint32_t F>
  inline Target real_constant()
  {
    boost::dispatch::functor< tag::Realpattern<F,D> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint32_t F>
  inline Target single_constant()
  {
    typename dispatch::make_functor<tag::Realpattern<F,0>, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D>
  inline Target double_constant()
  {
    typename dispatch::make_functor<tag::Realpattern<0,D>, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, uint64_t Value> inline Target Const()
  {
    typedef tag::Realpattern<boost::simd::uint32_t(Value),Value> patterns;
    typename dispatch::make_functor<patterns, Target>::type callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/simd/constant/common.hpp>

#endif
