//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_BROADCAST_HPP_INCLUDED

#include <boost/simd/swar/functions/broadcast.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::cpu_
                                    , (A0)(X)(A1)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return splat<A0>( extract<A1::value>(a0) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return boost::simd::broadcast<A1::value>(evaluate(a0));
    }
  };
} } }

#endif
