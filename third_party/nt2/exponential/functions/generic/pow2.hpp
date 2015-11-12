//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW2_HPP_INCLUDED

#include <nt2/exponential/functions/pow2.hpp>
#include <boost/assert.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/simd/fast_ldexp.hpp>
#include <nt2/include/functions/simd/toint.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <nt2/include/functions/simd/is_finite.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::fast_ldexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      BOOST_ASSERT_MSG(boost::simd::assert_all(is_finite(a1)),
                       "pow2 is not defined for an invalid second parameter");
      #endif
      return nt2::fast_ldexp(a0, nt2::toint(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< integer_<A0> >)
                              (generic_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::fast_ldexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (generic_< integer_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return nt2::fast_ldexp(One<A0>(), a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      BOOST_ASSERT_MSG(boost::simd::assert_all(is_finite(a0)),
                       "pow2 with one parameter is not defined for an invalid entry");
      #endif
      return nt2::fast_ldexp(One<A0>(), toint(a0));
    }
  };
} }

#endif
