//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DELTAC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DELTAC_HPP_INCLUDED

#include <nt2/include/functions/deltac.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deltac_, tag::cpu_
                            , (A0)(A1)(AST)(T)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                              ((ast_<AST, nt2::container::domain>))
                              ((target_<scalar_<unspecified_<T> > > ))
                            )
  {
    typedef typename nt2::meta::call<tag::as_size_(AST const&)>::type T1;
    typedef typename nt2::meta::call<tag::deltac_(A0 const&, A1 const&, T1, T)>::type result_type;
    BOOST_FORCEINLINE result_type operator()( const A0& i, const A1& j, const AST& siz, T const& )
    {
      return nt2::deltac(i, j, nt2::as_size(siz), T());
    }
  };
} }

#endif
