//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LINSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LINSPACE_HPP_INCLUDED

#include <nt2/core/functions/linspace.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/details/linspace.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linspace_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                            )
  {
    typedef meta::constant_<nt2::tag::linspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::linspace_
                                          , container::domain
                                          , of_size_<1,100>
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A0 const& u) const
    {
      return  boost::proto::
              make_expr < nt2::tag::linspace_
                        , container::domain
                        > ( of_size_<1,100>()
                          , constant_t(l,u,100)
                          , meta::as_<A0>()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linspace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef meta::constant_<nt2::tag::linspace_,A0> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::linspace_
                                          , container::domain
                                          , _2D
                                          , constant_t
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A0 const& u, A1 const& n) const
    {
      return  boost::proto::
              make_expr < nt2::tag::linspace_
                        , container::domain
                        > ( of_size(1,n)
                          , constant_t( (n<2 ? u : l), u, (n<2 ? 2 : n) )
                          , meta::as_<A0>()
                          );
    }
  };
} }

#endif
