//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FREQSPACE_HPP_INCLUDED

#include <nt2/core/functions/freqspace.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , _2D
                                          , meta::as_<double>
                                          , A0
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator ()(A0 a0) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( _2D(1,1+a0/2)
                            , meta::as_<double>()
                            , a0
                            );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (target_< scalar_<floating_<A1> > >)
                            )
  {
    typedef typename A1::type r_t;

    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , _2D, A1, A0
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator ()(A0 a0,const A1& a1) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( _2D(1,1+a0/2), a1, a0 );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , _2D
                                          , meta::as_<double>
                                          , A0, A1
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator ()(A0 a0, const A1& a1) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( _2D(1,a0)
                            , meta::as_<double>()
                            , a0, a1
                            );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< integer_<A0> >)
                              (unspecified_<A1>)
                              (target_< scalar_<floating_<A2> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::freqspace_
                                          , container::domain
                                          , _2D, A2, A0, A1
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator ()(A0 a0, const A1& a1, const A2& a2) const
    {
      return  boost::proto
              ::make_expr < nt2::tag::freqspace_
                          , container::domain
                          > ( _2D(1,a0), a2, a0, a1 );
    }
  };
} }

#endif
