//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LOGSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LOGSPACE_HPP_INCLUDED

#include <nt2/core/functions/logspace.hpp>
#include <nt2/core/functions/details/logspace.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/constants/log10_pi.hpp>
#include <nt2/include/constants/pi.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                            )
  {
    typedef meta::constant_<nt2::tag::logspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::logspace_
                                          , container::domain
                                          , of_size_<1,50>
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A0 const & uu) const
    {
      // This is matlab!
      A0 u = (uu ==  nt2::Pi<A0>()) ? nt2::Log10_pi<A0>() : uu;
      return  boost::proto::
              make_expr < nt2::tag::logspace_
                        , container::domain
                        > ( of_size_<1,50>()
                          , constant_t(l,u,50)
                          , meta::as_<A0>()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_, tag::cpu_
                            , (A0)(A2)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                              (target_ < unspecified_ < A2> >)
                            )
  {
    typedef meta::constant_<nt2::tag::logspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::logspace_
                                          , container::domain
                                          , of_size_<1,50>
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& l, A0 const & u, A2 const &) const
    {
      return  boost::proto::
              make_expr < nt2::tag::logspace_
                        , container::domain
                        > ( of_size_<1,50>()
                          , constant_t(l,u,50)
                          , meta::as_<A0>()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef meta::constant_<nt2::tag::logspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::logspace_
                                          , container::domain
                                          , _2D
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& uu, A1 const& n) const
    {
      //This is matlab!
      A0 u = (uu ==  nt2::Pi<A0>()) ? nt2::Log10_pi<A0>() : uu;

      return  boost::proto::
              make_expr < nt2::tag::logspace_
                        , container::domain
                        > ( of_size(1,n)
                          , constant_t ( (n<2 ? u : l), u, (n<2 ? 2 : n) )
                          , meta::as_<A0>()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                              (scalar_< integer_ <A1> >)
                              (target_ < unspecified_ < A2> >)
                            )
  {
    typedef meta::constant_<nt2::tag::logspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::logspace_
                                          , container::domain
                                          , _2D
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& l, A0 const & u,  A1 const &n, A2 const &) const
    {
      return  boost::proto::
              make_expr < nt2::tag::logspace_
                        , container::domain
                        > ( of_size(1,n)
                          , constant_t(l,u,n)
                          , meta::as_<A0>()
                          );
    }
  };
} }

#endif
