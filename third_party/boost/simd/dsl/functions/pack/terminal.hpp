//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_PACK_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_PACK_TERMINAL_HPP_INCLUDED

#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::terminal_, tag::cpu_
                                   , (Expr)(X)
                                   , ((expr_< target_< simd_< unspecified_<Expr>, X> >, boost::simd::tag::terminal_, mpl::long_<0> >))
                                   )
  {
    typedef typename boost::dispatch::meta::
            semantic_of<typename Expr::proto_child0>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()( Expr& ) const
    {
      return result_type();
    }
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, std::size_t N>
  struct semantic_of< as_< boost::simd::pack<T, N> > >
  {
    typedef as_< typename boost::simd::pack<T, N>::data_type > type;
  };
} } }

#endif
