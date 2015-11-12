//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FUNCTION_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FUNCTION_INDEX_HPP_INCLUDED

#include <nt2/core/functions/function_index.hpp>
#include <nt2/core/functions/aggregate.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_index_, tag::cpu_
                            , (I)(N)(Sz)(Idx)
                            , ((node_<I, nt2::tag::aggregate_, N, nt2::container::domain>))
                              (fusion_sequence_<Sz>)
                              (target_< unspecified_<Idx> >)
                            )
  {
    typedef typename nt2::make_size<I::proto_arity_c>::type    size_type;
    typedef typename boost::proto::result_of::
                     make_expr < nt2::tag::function_index_
                               , container::domain
                               , I
                               , typename boost::remove_const<Sz>::type
                               , size_type
                               , Idx
                               >::type                              result_type;

    result_type operator()(I const& i, Sz const& sz, Idx const& idx) const
    {
      size_type compact(sz);
      return boost::proto::make_expr< tag::function_index_
                                    , container::domain
                                    >( i, sz, compact, idx);
    }
  };
} }

#endif
