//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_ROT90_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_ROT90_HPP_INCLUDED

#include <nt2/linalg/functions/rot90.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/fliplr.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rot90_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<arithmetic_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rot90_0_, tag::cpu_
                            , (A0)
                            , (scalar_<arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rot90_0_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::fliplr(nt2::trans(a0))
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::rot90_, N,nt2::container::domain> ))
                            )
  {
    typedef A0& result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(in.extent());
      int k = ((boost::proto::child_c<1>(in)%4)+4)%4;
      if(k == 1)       out = nt2::fliplr(nt2::trans(boost::proto::child_c<0>(in)));
      else if(k == 2)  out = nt2::fliplr(nt2::flipud(boost::proto::child_c<0>(in)));
      else if(k == 3)  out = nt2::trans(nt2::flipud(boost::proto::child_c<0>(in)));
      else out = boost::proto::child_c<0>(in);
      return out;
    }
  };

} }


#endif
