//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_IFVECTVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_IFVECTVERT_HPP_INCLUDED

#include <nt2/core/functions/ifvectvert.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/of_size/predef.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::ifvectvert_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    // TODO: static size
    typedef typename nt2::make_size<c0_t::extent_type::static_size>::type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type siz;
      siz[0] = nt2::numel(boost::proto::child_c<0>(e));
      if(nt2::isvector(boost::proto::child_c<0>(e)))
        return siz;
      else
        return extent(boost::proto::child_c<0>(e));
    }
  };
} }

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ifvectvert_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} }

#endif
