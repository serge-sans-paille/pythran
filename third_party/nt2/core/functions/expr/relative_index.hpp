//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED

#include <nt2/core/functions/relative_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // When indexing an expression, evaluate a type with right cardinal then convert
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;
    typedef typename boost::simd::meta::
            vector_of< typename A0::value_type
                     , meta::cardinal_of<result_type>::value
                     >::type value_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& idx, const A1& bi, const A2&, const A3& p, const A4&) const
    {
      return nt2::splat<result_type>(nt2::run(idx,p,meta::as_<value_type>())-(typename A0::value_type)bi);
    }
  };

  //============================================================================
  // When indexing a scalar, evaluate as scalar type of expression then convert
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)(A3)(A4)
                            , ((expr_ < scalar_< unspecified_<A0> >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& idx, const A1& bi, const A2&, const A3&, const A4&) const
    {
      return nt2::splat<result_type>(nt2::run(idx,0u,meta::as_<typename A0::value_type>())-(typename A0::value_type)bi);
    }
  };
} }

#endif
