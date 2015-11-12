//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_GAMMAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_GAMMAINC_HPP_INCLUDED

#include <nt2/euler/functions/gammainc.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/gammainc.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/sdk/error/policies.hpp>
#include <boost/math/special_functions/gamma.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_ gammainc(x, a)
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammainc_, tag::cpu_
                              , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0, A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::gammainc(nt2::tofloat(a0), nt2::tofloat(a1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammainc_, tag::cpu_
                              , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A1> >)
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& x, const A1& a) const
    {
      if (nt2::is_eqz(a)|| nt2::eq(x, nt2::Inf<result_type>())) return nt2::One<result_type>();
      return boost::math::gamma_p(a, x, nt2_policy());
    }
  };
} }

#endif
