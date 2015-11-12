//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FILL_PATTERN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FILL_PATTERN_HPP_INCLUDED

#include <nt2/core/functions/fill_pattern.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fill_pattern_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::fill_pattern_
                                , container::domain
                                , typename boost::remove_const<A1>::type
                                , A0 const&
                                , std::size_t
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& p, A1 const& sz) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::fill_pattern_
                        , container::domain
                        > ( sz, boost::cref(p), nt2::numel(p) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fill_pattern_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, ( A0 const& a0, A1 const& a1 )
                          , (nt2::fill_pattern(a0,nt2::as_size(a1)))
                          )
  };
} }

#endif
