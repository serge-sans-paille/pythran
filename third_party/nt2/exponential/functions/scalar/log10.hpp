//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG10_HPP_INCLUDED

#include <nt2/exponential/functions/log10.hpp>
#include <boost/assert.hpp>
#include <nt2/include/functions/scalar/log10.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_
                            , boost::simd::tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, unsigned>::type ui_type;
      BOOST_ASSERT_MSG( a0 > 0, "log10 is not defined for zero or negative integers." );
      return static_cast<result_type>(log10(static_cast<ui_type>(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::cpu_
                            , (A0)
                            , (scalar_< uint8_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return (a0 >= 100u) ? 2 : (a0 >= 10u) ? 1 : 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::cpu_
                            , (A0)
                            , (scalar_< uint16_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return (a0 >= 10000u) ? 4 :
        (a0 >= 1000u) ? 3 : (a0 >= 100u) ? 2 : (a0 >= 10u) ? 1 : 0;
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::cpu_
                            , (A0)
                            , (scalar_< uint32_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return (a0 >= 1000000000u) ? 9 : (a0 >= 100000000u) ? 8 : (a0 >= 10000000u) ? 7 :
        (a0 >= 1000000u) ? 6 : (a0 >= 100000u) ? 5 : (a0 >= 10000u) ? 4 :
        (a0 >= 1000u) ? 3 : (a0 >= 100u) ? 2 : (a0 >= 10u) ? 1 : 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::cpu_
                            , (A0)
                            , (scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return(a0 >= 10000000000000000000ull)? 19 :
        (a0 >= 1000000000000000000ull)? 18 :
        (a0 >= 100000000000000000ull)? 17 :
        (a0 >= 10000000000000000ull)? 16 :
        (a0 >= 1000000000000000ull)? 15 :
        (a0 >= 100000000000000ull)? 14 :
        (a0 >= 10000000000000ull)? 13 :
        (a0 >= 1000000000000ull)? 12 :
        (a0 >= 100000000000ull)? 11 :
        (a0 >= 10000000000ull)? 10 :
        (a0 >= 1000000000ull)? 9 :
        (a0 >= 100000000ull)? 8 :
        (a0 >= 10000000ull)? 7 :
        (a0 >= 1000000ull)? 6 :
        (a0 >= 100000ull)? 5 :
        (a0 >= 10000ull)? 4 :
        (a0 >= 1000ull)? 3 :
        (a0 >= 100ull)? 2 :
        (a0 >= 10ull)? 1 : 0;
    }

  };

} }

#endif
