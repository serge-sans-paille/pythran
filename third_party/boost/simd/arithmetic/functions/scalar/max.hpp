//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_MAX_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/max.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/max.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A0 a1) const
    {
      return (a0 > a1) ? a0 : a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (scalar_< arithmetic_<A1> >)
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 a1) const
    {
      return (A0::value > a1) ? A0::value : a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< arithmetic_<A0> >)
                                      (mpl_integral_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&) const
    {
      return (a0 > A1::value) ? a0 : A1::value;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (mpl_integral_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef typename  boost::mpl::max<A0,A1>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const&) const
    {
      return result_type();
    }
  };
} } }

#endif
