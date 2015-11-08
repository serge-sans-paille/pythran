//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYVALM_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYVALM_HPP_INCLUDED
#include <nt2/polynom/functions/polyvalm.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/mtimes.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyvalm_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)(scalar_<floating_<A1> > )
                            )
  {

    typedef typename A0::value_type value_type;
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      if (isempty(a0)) return Zero<A1>();
      A1 ans = a0(1);
      for(size_t i = 2; i <= numel(a0); ++i)
      {
        ans = fma(ans, a1, a0(i));
      }
      return ans;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::polyvalm_, N,nt2::container::domain> ))
                            )
  {
    typedef typename A0::value_type                                  value_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       poly_t;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type       matr_t;
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out = nt2::zeros(in.extent(), meta::as_<value_type>());
      BOOST_ASSERT_MSG(nt2::issquare(in), "input matrix must be square");
      BOOST_AUTO_TPL(p,  nt2::reduce( boost::proto::child_c<0>(in)));
      poly_t & m = boost::proto::child_c<1>(in);
      size_t n =  size(m, 1);
      BOOST_AUTO_TPL(pp,  nt2::expand_to(p, n, numel(p)));
      for(size_t i = 1; i <= nt2::numel(p); ++i)
      {
        out =  nt2::mtimes(out, m) + nt2::from_diag(pp(nt2::_, i));
      }
      return out;
    }

  };

} }


#endif
