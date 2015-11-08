//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_INT_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_INT_SPLAT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Int_splat generic tag

     Represents the Int_splat constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    template<boost::simd::int64_t I>
    struct Intpattern : ext::pure_constant_< Intpattern<I> >
    {
      typedef ext::pure_constant_< Intpattern<I> > parent;
      template<class Target, class Dummy=void>
      /// INTERNAL ONLY
      struct apply : meta::int_c< typename Target::type
                                , typename Target::type(I)
                                > {};
    };
  }

  template<class Target, typename boost::dispatch::meta::scalar_of<Target>::type N>
  inline Target integral_constant()
  {
    typedef tag::Intpattern<boost::simd::int64_t(N)> tag_t;
    typename dispatch::make_functor< tag_t, Target >::type callee;
    return callee( dispatch::meta::as_<Target>() );
  }
} }

#include <boost/simd/constant/common.hpp>

#endif
