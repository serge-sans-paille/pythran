//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SCALAR_LAGUERRE_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SCALAR_LAGUERRE_HPP_INCLUDED

#include <nt2/polynomials/functions/laguerre.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/dispatch/meta/as_floating.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::laguerre_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0,A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::laguerre(a0, result_type(a1));
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is floating_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::laguerre_, tag::cpu_,
                            (A0)(A1),
                            ((scalar_<integer_<A0> >))((scalar_<floating_<A1> > ))
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0,A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A1 p0 = One<A1>();
      if(a0 == 0) return p0;
      A1 p1 = p0-a1;
      A0 c = 1;
      while(c < a0)
      {
        std::swap(p0, p1);
        p1 = laguerre_next(c, a1, p0, p1);
        ++c;
      }
      return p1;
    }
  private:
    template <class T, class T1, class T2>
    static inline T
    laguerre_next(const uint32_t& n, const T& x, const T1 &Ln, const T2& Lnm1)
    {
      const T np1 = T(oneplus(n));
      return ((T(n) + np1 - x) * Ln - n *Lnm1) / np1;
    }
  };
} }

#endif
