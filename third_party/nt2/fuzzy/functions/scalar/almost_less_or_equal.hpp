//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SCALAR_ALMOST_LESS_OR_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SCALAR_ALMOST_LESS_OR_EQUAL_HPP_INCLUDED
#include <nt2/fuzzy/functions/almost_less_or_equal.hpp>
#include <nt2/include/functions/scalar/successor.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/scalar/logical_or.hpp>
#include <boost/simd/sdk/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::almost_less_or_equal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef typename meta::as_logical<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return result_type(a0 <= a1+abs(a2));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::almost_less_or_equal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef typename meta::as_logical<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      if (a0 == a1) return True<result_type>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (logical_or(is_inf(a0), is_inf(a1))) return result_type(a0 == a1);
      if (logical_or(is_nan(a0), is_nan(a1))) return False<result_type>();
#endif
      // see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
      // by Bruce Dawson
      // Do not choose a2 negative or too large
      // assert(aa2 > 0 && aa2 < bitinteger(Nan<select_type>()) );
      return  result_type(a0 <= successor(a1, nt2::abs(a2)));
    }
  };
} }


#endif
