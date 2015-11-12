//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SCALAR_FUZZY_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SCALAR_FUZZY_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#include <nt2/fuzzy/functions/fuzzy_definitely_not_equal.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/dist.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fuzzy_definitely_not_equal_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(nt2::dist(a0, a1) > a2*nt2::max(nt2::abs(a0),nt2::abs(a1)));
    }
  };
} }


#endif
