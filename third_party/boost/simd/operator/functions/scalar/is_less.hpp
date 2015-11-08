//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_IS_LESS_HPP_INCLUDED

#include <boost/simd/operator/functions/is_less.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(a0 < a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< fundamental_<A0> >)
                                      (mpl_integral_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&) const
    {
      return result_type(a0 < A1::value);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (scalar_< fundamental_<A1> >)
                                    )
  {
    typedef typename meta::as_logical<A1>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 a1) const
    {
      return result_type(A0::value < a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_, tag::cpu_
                                    , (A0)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (mpl_integral_< scalar_< fundamental_<A0> > >)
                                    )
  {
    typedef typename meta::as_logical<typename A0::value_type>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A0 const&) const
    {
      return result_type(false);
    }
  };
} } }

#endif
