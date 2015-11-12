//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_FACTOR_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_FACTOR_HPP_INCLUDED
#include <nt2/combinatorial/functions/factor.hpp>
#include <nt2/include/functions/primes.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/maxflint.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/is_signed.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factor_, tag::cpu_,
                      (A0),
                      (scalar_ < integer_<A0> > )
                      )
  {
    typedef nt2::container::table<A0>  result_type;
    inline result_type operator()(A0 n) const
    {
      check(n, typename meta::is_signed<A0>::type());
      typedef nt2::container::table<std::ptrdiff_t> itab_t;
      result_type f, f1;
      if (n < 4)
      {
        f = n;
        return f;
      }
      else
        f = nt2::zeros(1, 0, nt2::meta::as_<A0>());
      result_type p = nt2::primes(nt2::sqrt(n));
      while (n>1)
      {
        itab_t d = nt2::find(nt2::is_eqz(nt2::rem(n,p)));
        if (nt2::isempty(d))
        {
          f1 = nt2::cath(f, n);
          f =  f1;  //ALIASING !
          break;
        }
        result_type p1 = rowvect(p(d));
        p = p1;
        f1 = nt2::cath(f, p);
        f =  f1; //ALIASING !
        n = n/nt2::prod(p);
      }
      return nt2::sort(f, 2);
    }
  private :
    inline void check(A0 const&, boost::mpl::false_ const &) const {}
    inline void check(A0 const& n, boost::mpl::true_ const &) const
    {
      BOOST_ASSERT_MSG(n > 0, "primes : input must be greater than zero");
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factor_, tag::cpu_,
                      (A0),
                      (scalar_ < floating_<A0> > )
                      )
  {
    typedef nt2::container::table<A0>  result_type;
    inline result_type operator()(A0 n) const
    {
      check(n);
      typedef nt2::container::table<std::ptrdiff_t> itab_t;
      result_type f, f1;
      if (n < Four<A0>())
      {
        f = n;
        return f;
      }
      else
        f = nt2::zeros(1, 0, nt2::meta::as_<A0>());
      result_type p = nt2::primes(nt2::sqrt(n));
      while (n>1)
      {
        itab_t d = nt2::find(nt2::is_eqz(nt2::rem(n,p)));
        if (nt2::isempty(d))
        {
          f1 = nt2::cath(f, n);
          f =  f1;  //ALIASING !
          break;
        }
        result_type p1 = rowvect(p(d));
        p = p1;
        f1 = nt2::cath(f, p);
        f =  f1; //ALIASING !
        n = n/nt2::prod(p);
      }
      return nt2::sort(f, 2);
    }
  private :
    inline void check(A0 const& n) const
    {
      BOOST_ASSERT_MSG(n <= Maxflint<A0>(), "primes : When input is floating, its maximum allowed value is Maxflint");
      BOOST_ASSERT_MSG(n > 0, "primes : input must be greater than zero");
    }
  };
} }
#endif

