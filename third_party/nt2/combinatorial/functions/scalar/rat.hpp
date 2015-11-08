//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_RAT_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_RAT_HPP_INCLUDED
#include <nt2/combinatorial/functions/rat.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/eps.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_finite.hpp>
#include <nt2/include/functions/scalar/is_not_finite.hpp>
#include <nt2/include/functions/scalar/is_not_nan.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/round2even.hpp>
#include <nt2/include/functions/scalar/sign.hpp>
#include <nt2/include/functions/vertcat.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rat_, tag::cpu_
                            , (A0)
                            , ( scalar_<floating_<A0> > )
                              ( scalar_ <floating_<A0> > )
                              ( scalar_ <floating_ <A0> >)
    )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0, A0 & n, A0 & d) const
    {
      A0 tol = A0(1.e-6)*nt2::abs(a0);
      rat(a0, tol, n, d);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rat_, tag::cpu_
                            , (A0)
                            , ( scalar_<floating_<A0> >)
                              ( scalar_<floating_<A0> >)
                              ( scalar_<floating_<A0> >)
                              ( scalar_<floating_<A0> >)
    )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0,A0 const& tol, A0 & n, A0 & d) const
    {
      typedef nt2::container::table<A0> tab_t;
      A0 x = a0;
      n = Zero<A0>();
      d = Zero<A0>();
      #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_not_finite(x))
      { // Special case for inf, -inf, NaN
        if (is_not_nan(x)) n = nt2::sign(x);
      }
      else
      #endif
      {
        size_t k = 0;
        tab_t c = nt2::eye(2, meta::as_<A0>());
        while (true)
        {
          ++k;
          d = nt2::round2even(x);
          if (nt2::is_finite(x))
          {
            x -= d;
            tab_t c0 = nt2::vertcat(d, One<A0>());
            tab_t c1 = nt2::mtimes(c, c0);
            tab_t c2 = nt2::vertcat(c(1, 1), c(1, 2));
            c =        nt2::horzcat(c1, c2);
          }
          else // Special case for +/- inf
          {
            c =  horzcat(vertcat(x,Zero<A0>()), c(nt2::_, 1));
          }
          if (nt2::is_eqz(x) || (nt2::abs(c(1,1)/c(2,1) - a0) <= nt2::max(tol,nt2::eps(x))))
            break;
          x = rec(x);
        }
        n = c(1,1)/nt2::sign(c(2,1));
        d = nt2::abs(c(2,1));
      }
    }
  };
} }

#endif
