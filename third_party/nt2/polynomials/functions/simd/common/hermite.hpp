//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SIMD_COMMON_HERMITE_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SIMD_COMMON_HERMITE_HPP_INCLUDED

#include <nt2/polynomials/functions/hermite.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hermite_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<arithmetic_<A1>,X>))
                            )
  {

    typedef typename meta::as_floating<A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::hermite(a0, tofloat(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hermite_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<floating_<A1>,X>))
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A1 p0 = One<A1>();
      if(a0==0) return p0;
      A1 p1 = a1+a1;
      A1 p;
      A1 vc =  One<A1>();
      uint32_t c = 1;
      while(c < (typename meta::as_unsigned<A0>::type)a0)
      {
        p = p0;
        p0 = p1;
        p1 = Two<A1>()*(a1*p0-vc*p);
        vc += One<A1>();
        ++c;
      }
      return p1;
    }
  };
} }


#endif
