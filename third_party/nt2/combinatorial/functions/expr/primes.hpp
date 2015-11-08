//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_PRIMES_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_PRIMES_HPP_INCLUDED
#include <nt2/combinatorial/functions/primes.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::primes_, tag::cpu_,
                      (A0),
                      (scalar_ < arithmetic_<A0> > )
                      )
  {
    typedef nt2::container::table<A0>  result_type;
    inline result_type operator()(A0 const& n) const
    {
      if (n < 2) return zeros(1,0,meta::as_<A0>());
      result_type p = _(One<A0>(), Two<A0>(), n);
      size_t q = length(p);
      size_t l = nt2::sqrt(n);
      p(1) = Two<A0>();
      for (size_t k = 3; k <= l; k+= 2)
        {
          if (p((k+1) >>  1))
            p(_((sqr(k)+1) >> 1, k, q)) = Zero<A0>();
        }
      return p(is_gtz(p)) ;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::primes_, tag::cpu_,
                      (A0),
                      (scalar_ < floating_<A0> > )
                      )
  {
    typedef nt2::container::table<A0>  result_type;
    inline result_type operator()(A0 const& n) const
    {
      if (n < 2) return zeros(1,0,meta::as_<A0>());
      result_type p = _(One<A0>(), Two<A0>(), n);
      size_t q = length(p);
      size_t l = nt2::sqrt(n);
      p(1) = Two<A0>();
      for (size_t k = 3; k <= l; k+= 2)
        {
          if (p((k+1) >>  1))
            p(_((sqr(k)+1) >> 1, k, q)) = Zero<A0>();
        }
      return p(is_gtz(p)) ;
    }
  };
} }
#endif
