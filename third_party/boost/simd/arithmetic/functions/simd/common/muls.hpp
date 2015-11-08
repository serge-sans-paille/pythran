//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/split_multiplies.hpp>
#include <boost/simd/include/functions/simd/groups.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::muls_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>, X>))
                                      ((simd_<floating_<A0>, X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0*a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::muls_, tag::cpu_
                                       , (A0)(X)
                                       , ( simd::meta::is_upgradable_on_ext<A0,X> )
                                       , ((simd_<integer_<A0>, X>))
                                         ((simd_<integer_<A0>, X>))
                                       )
  {

    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype res0, res1;
      split_multiplies(a0, a1, res0, res1);
      return groups(res0, res1);
    }
  };
} } }

#endif
