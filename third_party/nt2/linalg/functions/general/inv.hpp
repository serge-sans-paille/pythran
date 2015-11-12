//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED

#include <nt2/linalg/functions/inv.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/getri.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/meta/concrete.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/error/warning.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::inv_
                                      , N , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0& result_type;
    typedef typename  meta::concrete<A0>::type          c_t;
    typedef typename  A0::value_type                    c_type;
    typedef typename  nt2::meta::as_real<c_type>::type  base_t;

    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_ASSERT_MSG( issquare(boost::proto::child_c<0>(in))
                      , "INV: Argument must be a square matrix"
                      );

      // If needed, resize
      out.resize(nt2::extent(in));

      // Reuse output memory if possible
      c_t tmp = shallow_concrete(out, boost::proto::child_c<0>(in));

      nt2::container::table<nt2_la_int> ip;

      // Factorize A as L/U and call tri
      nt2::getrf(boost::proto::value(tmp),boost::proto::value(ip));
      nt2::getri(boost::proto::value(tmp),boost::proto::value(ip));

      NT2_WARNING ( ( rcond_(boost::proto::child_c<0>(in),tmp) >= nt2::Eps<base_t>())
                  , "INV: matrix is singular to machine precision."
                  );

      return out = tmp;
    }

    template<typename V, typename L>
    static base_t rcond_(V const& a0, L const& lu)
    {
      return nt2::rec(nt2::mnorm1(a0) * nt2::mnorm1(lu));
    }
  };

} }

#endif
