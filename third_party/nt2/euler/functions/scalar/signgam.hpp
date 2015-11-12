//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_SIGNGAM_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_SIGNGAM_HPP_INCLUDED

#include <nt2/euler/functions/signgam.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/is_lez.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>

#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::signgam_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type type;
#ifdef BOOST_SIMD_NO_INVALIDS
      if (nt2::is_lez(a0))
      {
        if (nt2::is_flint(a0))
          return nt2::Nan<type>();
        else
          return nt2::One<type>()-bool(nt2::is_odd(nt2::floor(a0)))*nt2::Two<A0>();
      }
#else
      if (nt2::is_lez(a0))
      {
        if (nt2::is_flint(a0)||nt2::is_inf(a0))
          return nt2::Nan<type>();
        else
          return nt2::One<type>()-bool(nt2::is_odd(nt2::floor(a0)))*nt2::Two<A0>();
      }
      else if (nt2::is_nan(a0)) return a0;
#endif
      return nt2::One<type>();
    }
  };
} }


#endif
