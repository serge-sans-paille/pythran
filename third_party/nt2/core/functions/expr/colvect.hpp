//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_COLVECT_HPP_INCLUDED

#include <nt2/core/functions/colvect.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::colvect_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type::extent_type ext_t;
    typedef typename meta::call<tag::numel_(ext_t const&)>::type num;

    typedef of_size_< mpl_value<num>::value > result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(nt2::numel(boost::proto::child_c<0>(e)));
    }
  };
} }

#endif
