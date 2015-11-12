//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_REALPOW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_REALPOW_HPP_INCLUDED
#include <nt2/exponential/functions/realpow.hpp>
#include <boost/assert.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/is_nltz.hpp>
#include <nt2/include/functions/scalar/pow.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::realpow_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_ASSERT_MSG( is_nltz(a0) || is_flint(a1),
                        "realpow cannot produce complex result." );
      return  pow(a0, a1);
    }
  };
} }

#endif
