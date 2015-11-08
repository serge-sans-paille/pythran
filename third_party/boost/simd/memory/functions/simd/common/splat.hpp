//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED

#include <boost/simd/memory/functions/splat.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/tofloat.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/functions/simd/touint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/preprocessor/make.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/simd/meta/is_logical_mask.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // With no idea what we're doing, just fill the vector piecewise
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::splat_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , (scalar_< unspecified_<A0> >)
                                      ((target_< simd_< unspecified_<A1>, X > >))
                                    )
  {
    typedef typename A1::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type sA1;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return eval(a0,typename simd::meta::cardinal_of<result_type>::type());
    }

    #define M0(z, n, t) static_cast<sA1>(a0)

    BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(1, M0)

    #undef M0
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::splat_, tag::cpu_
                                       , (A0)(A1)(X)(Y)
                                       , (mpl::equal_to
                                        < boost::simd::meta::cardinal_of<A0>
                                          ,  boost::simd::meta
                                          ::cardinal_of<typename A1::type>
                                        >
                                        )
                                       , ((simd_< unspecified_<A0>, X >))
                                         ((target_< simd_< unspecified_<A1>, Y > >))
                                       )
  {
    typedef typename A1::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type sA1;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return eval(a0,typename simd::meta::cardinal_of<result_type>::type());
    }

    #define M0(z, n, t) static_cast<sA1>(extract<n>(a0))

    BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(1, M0)

    #undef M0
  };

  //============================================================================
  // Splatting a SIMD value to another can use toint, touint or tofloat (optimizations)
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::splat_, tag::cpu_
                                       , (A0)(A1)(X)
                                       , (mpl::equal_to
                                           < boost::simd::meta::cardinal_of<A0>
                                           , boost::simd::meta
                                             ::cardinal_of<typename A1::type>
                                           >
                                         )
                                       , ((simd_< arithmetic_<A0>, X >))
                                         ((target_< simd_< floating_<A1>, X > >))
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return simd::tofloat(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::splat_, tag::cpu_
                                       , (A0)(A1)(X)
                                       , (mpl::equal_to
                                           < boost::simd::meta::cardinal_of<A0>
                                           , boost::simd::meta
                                             ::cardinal_of<typename A1::type>
                                           >
                                         )
                                       , ((simd_< arithmetic_<A0>, X >))
                                         ((target_< simd_< int_<A1>, X > >))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      // bitwise_cast because long vs long long for same width
      return bitwise_cast<result_type>(simd::toint(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::splat_, tag::cpu_
                                       , (A0)(A1)(X)
                                       , (mpl::equal_to
                                           < boost::simd::meta::cardinal_of<A0>
                                           , boost::simd::meta
                                             ::cardinal_of<typename A1::type>
                                           >
                                         )
                                       , ((simd_< arithmetic_<A0>, X >))
                                         ((target_< simd_< uint_<A1>, X > >))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      // bitwise_cast because long vs long long for same width
      return bitwise_cast<result_type>(simd::touint(a0));
    }
  };

  //============================================================================
  // splat logical is genmask + splat
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::splat_, tag::cpu_
                                       , (A0)(A1)(X)
                                       , (boost::simd::meta::is_logical_mask<typename A1::type>)
                                       , (scalar_< unspecified_<A0>  >)
                                         ((target_< simd_< logical_<A1>, X > >))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef typename meta::scalar_of<typename result_type::type>::type stype;
      return bitwise_cast<result_type>(splat<typename result_type::type>(a0 ? Allbits<stype>() : Zero<stype>()));
    }
  };
} } }

#endif
