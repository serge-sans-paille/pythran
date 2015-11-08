//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_PINV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_PINV_HPP_INCLUDED

#include <nt2/linalg/functions/pinv.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/gt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <nt2/include/constants/mone.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::pinv_, N,nt2::container::domain> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       Out0;
    typedef A0&                                                   result_type;
    typedef typename A0::value_type                                value_type;
    typedef typename nt2::meta::as_real<value_type>::type             rtype_t;
    typedef nt2::table<value_type>                                 entry_type;
    typedef nt2::table<rtype_t>                                     base_type;

    result_type operator()(A0& out, const A1& in) const
    {
      entry_type u,tv;
      base_type s;

      out.resize(in.extent());
      rtype_t tol = choice(in, N());
      out = boost::proto::child_c<0>(in);

      nt2::tie(u, s, tv) = svd(out, nt2::raw_);

      rtype_t epsi = (tol <0  ? nt2::eps(s(1)) : tol)*length(out);
      entry_type w1 = nt2::if_else( nt2::gt(s, epsi), nt2::rec(s), nt2::Zero<rtype_t>());
      out = mtimes(ctrans(tv), mtimes(from_diag(w1), ctrans(u)));

      return out;
    }
  private :
    static rtype_t choice(const A1&, boost::mpl::long_<1> const &)
    {
      return Mone<rtype_t>();
    }

    static rtype_t choice(const A1& in, boost::mpl::long_<2> const &)
    {
      return boost::proto::child_c<1>(in);
    }
  };


} }

#endif
