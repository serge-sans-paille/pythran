//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SCALAR_LEGENDRE_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SCALAR_LEGENDRE_HPP_INCLUDED
#include <nt2/polynomials/functions/legendre.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/include/functions/scalar/abs.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::legendre_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return legendre(a0, result_type(a1));
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is floating_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::legendre_, tag::cpu_,
                             (A0)(A1),
                             (scalar_<integer_<A0> >)(scalar_<floating_<A1> >)
                             )
  {
    typedef A1 result_type;
    typedef typename  meta::as_unsigned<A0>::type utype;
    NT2_FUNCTOR_CALL(2)
      {
        if(nt2::abs(a1) > 1) return Nan<A1>();
        A1 p0 = One<A1>();
        if(a0 == 0)  return p0;
        A1 p1 = a1;
        utype n =  1;
        const utype l = utype(a0);
        while(n < l)
          {
            std::swap(p0, p1);
            p1 = legendre_next(n, a1, p0, p1);
            ++n;
          }
        return p1;
      }
  private :
    template <class T1, class T2, class T3 >
      static inline T1
      legendre_next(const utype& l,const T1& x, const T2& Pl, const T3& Plm1)
      {
        return ((2*l+1)*x*Pl-l*Plm1)/(l+1);
      }
  };
} }

#endif
