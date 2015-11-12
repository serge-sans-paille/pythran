//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::frexp_, tag::cpu_
                                      , (A0)(A2)
                                      , ( boost::is_same
                                          < typename dispatch::meta
                                                      ::as_integer<A0>::type
                                          , A2
                                          >
                                        )
                                      , ((generic_< floating_<A0> >))
                                        ((generic_< integer_<A2> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A2 & a2) const
    {
      A0 a1;
      boost::simd::frexp(a0, a1, a2);
      return a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::frexp_, tag::cpu_
                                    , (A0)
                                    , ((generic_<floating_<A0> >))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type exponent;
    typedef std::pair<A0,exponent>                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first;
      exponent second;
      boost::simd::frexp( a0, first, second );
      return result_type(first, second);
    }
  };
} } }

#endif
