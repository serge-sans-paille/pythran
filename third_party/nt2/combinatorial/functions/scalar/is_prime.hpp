//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_IS_PRIME_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_IS_PRIME_HPP_INCLUDED

#include <nt2/combinatorial/functions/is_prime.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/primes.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::is_prime_, tag::cpu_
                            , (A0)
                            , ((scalar_<integer_<A0> >))
                            )
  {
    typedef typename meta::as_logical<A0>::type   result_type;

    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG( (a0 >  0) || !a0
                      , "is_prime input is out of range (< 0)"
                      );

      BOOST_ASSERT_MSG( a0 <=  A0(saturate<A0>(Valmax<uint32_t>()))
                      , "is_prime input is out of range"
                      );

      if (a0 <= 1) return  False<result_type>();
      A0 m = oneplus(nt2::sqrt(a0));
      nt2::container::table<A0> p = nt2::primes(m);

      ///TODO perhaps a while with precox ending
      return result_type(nt2::globalall(nt2::rem(a0, p(nt2::lt(p, a0)))));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::is_prime_, tag::cpu_
                            , (A0)
                            , ((scalar_<floating_<A0> >))
                            )
  {
    typedef typename meta::as_logical<A0>::type     result_type;

    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(a0 >= 0, "is_prime input is out of range (< 0)");
      BOOST_ASSERT_MSG(is_flint(a0), "is_prime input is not integral");
      BOOST_ASSERT_MSG( a0 <=  Valmax<uint32_t>()
                      , "is_prime input is out of range"
                      );

      if (a0 <= 1) return False<result_type>();

      uint32_t ia0 = a0;
      nt2::container::table<uint32_t> p = nt2::primes(oneplus(sqrt(ia0)));

      ///TODO perhaps a while with precox ending
      return result_type(nt2::globalall(nt2::rem(ia0, p(lt(p, ia0)))));
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::is_prime_, tag::cpu_
                            , (A0)(A1)
                            , ((scalar_<integer_<A0> >))
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::as_logical<A0>::type   result_type;

    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( (a0 >  0) || !a0
                      , "is_prime input is out of range (< 0)"
                      );

      BOOST_ASSERT_MSG( a0 <=  A0(saturate<A0>(Valmax<uint32_t>()))
                      , "is_prime input is out of range"
                      );

      if (a0 <= 1) return  False<result_type>();
      return result_type(nt2::globalall(nt2::rem(a0, a1(nt2::lt(a1, a0)))));
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::is_prime_, tag::cpu_
                            , (A0)(A1)
                            , ((scalar_<floating_<A0> >))
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::as_logical<A0>::type     result_type;

    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(a0 >= 0, "is_prime input is out of range (< 0)");
      BOOST_ASSERT_MSG(is_flint(a0), "is_prime input is not integral");
      BOOST_ASSERT_MSG( a0 <=  Valmax<uint32_t>()
                      , "is_prime input is out of range"
                      );

      if (a0 <= 1) return False<result_type>();
      uint32_t ia0 = a0;

      return result_type(nt2::globalall(nt2::rem(ia0, a1(nt2::lt(a1, ia0)))));
    }
  };
} }

#endif
