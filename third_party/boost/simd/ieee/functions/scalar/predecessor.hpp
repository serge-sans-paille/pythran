//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_PREDECESSOR_HPP_INCLUDED

#include <boost/simd/ieee/functions/predecessor.hpp>
#include <boost/simd/include/functions/scalar/bitfloating.hpp>
#include <boost/simd/include/functions/scalar/bitinteger.hpp>
#include <boost/simd/include/functions/scalar/minusone.hpp>
#include <boost/simd/include/functions/scalar/subs.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/is_gez.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::predecessor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (Valmin<A0>()+a1 > a0) return Valmin<A0>();
      return a0-a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::predecessor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return minusone(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::predecessor_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (is_nan(a0)) return a0;
      return bitfloating(subs(bitinteger(a0), itype(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::predecessor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0;
      return bitfloating(minusone(bitinteger(a0)));
    }
  };
} } }

#endif
