//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_COMBS_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_COMBS_HPP_INCLUDED
#include <nt2/combinatorial/functions/combs.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::combs_, tag::cpu_,
                             (A0)(A1),
                             (unspecified_<A0>)
                             (scalar_ < integer_<A1> > )
    )
  {
    typedef typename A0::value_type                        value_type;
    typedef nt2::container::table<value_type, _2D>        result_type;
    inline result_type operator()(A0 const& v0,  const A1 & m0) const
    {
      result_type p;
      size_t m = m0;
      size_t n = nt2::length(v0);
      if (n == m || n == 0)
      {
        return nt2::rowvect(v0);
      }
      else if (m == 1u)
      {
        return nt2::colvect(v0);
      }
      else
      {
        result_type v = nt2::rowvect(v0);

        p = nt2::zeros(0, 0, meta::as_<value_type>());
        if ((m < n) && (m > 1u))
        {
          for (size_t k = 1;  k <= n-m+1;  ++k)
          {
            result_type q = nt2::combs(v(nt2::_(k+1, n)),m-1);
            result_type tmp = nt2::cath(v(nt2::ones(size(q,1),1, meta::as_<ptrdiff_t>()),k), q);
            if (isempty(p))
              p =  tmp;
            else
            {
              result_type tmp1 =  nt2::catv(p,tmp);//ALIASING
              p =  tmp1;
            }
          }
        }
        return p;
      }
    }
  };
} }
#endif
