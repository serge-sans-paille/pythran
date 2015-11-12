//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SCALAR_PLEVL_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SCALAR_PLEVL_HPP_INCLUDED
#include <nt2/polynomials/functions/plevl.hpp>
#include <nt2/include/functions/scalar/tchebeval.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/fusion/adapted/array.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::plevl_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(fusion_sequence_<A1>)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return plevl(result_type(a0), a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::plevl_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)(fusion_sequence_<A1>)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typename A1::const_iterator p = a1.begin();
      A0 ans = a0+*p++;
      do
      ans = fma(ans, a0, *p);
      while( ++p !=  a1.end());
      return ans;
    }
  };
} }


#endif
