//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_REMQUO_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/remquo.hpp>
#include <boost/simd/include/functions/simd/round2even.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::remquo_
                                       , tag::cpu_
                                       , (A0)(A1)
                                       , ( boost::is_same
                                          < typename dispatch::meta::
                                                     as_integer<A0,signed>::type
                                          , A1
                                          >
                                         )
                                       , (generic_< floating_<A0> >)
                                         (generic_< floating_<A0> >)
                                         (generic_< integer_<A1> > )
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A0 const& a1,A1& a3) const
    {
      result_type a2;
      boost::simd::remquo(a0, a1, a2, a3);
      return a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::remquo_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type quo_t;
    typedef std::pair<A0,quo_t>                                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 const& a1) const
    {
      A0 first;
      quo_t second;
      boost::simd::remquo( a0, a1, first, second );
      return result_type(first, second);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::remquo_, tag::cpu_
                                       , (A0)(A1)
                                       , ( boost::is_same
                                           < typename dispatch::meta::
                                                      as_integer<A0,signed>::type
                                           , A1
                                           >
                                         )
                                       , (generic_<floating_<A0> >)
                                         (generic_<floating_<A0> >)
                                         (generic_<floating_<A0> >)
                                         (generic_<integer_ <A1> >)
                                       )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1,A0& a2, A1& a3) const
    {
      A0 const d = round2even(a0/a1);

#if defined(BOOST_SIMD_NO_INVALIDS)
      a2 = if_allbits_else(is_eqz(a1), a0-d*a1);
#else
      a2 = if_allbits_else(l_or(is_invalid(a0), is_eqz(a1)), a0-d*a1);
#endif

      a3 = toint(d);
    }
  };
} } }

#endif
