//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLON_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLON_RELATIVE_INDEX_HPP_INCLUDED

#include <nt2/core/functions/relative_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/core/container/extremum/category.hpp>
#include <nt2/core/container/colon/category.hpp>
#include <nt2/core/functions/details/colon.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // When indexing on _, return the consecutive positions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)(A3)(A4)
                            , ((expr_ < colon_< A0 >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0&, const A1&, const A2&, const A3& p, const A4&) const
    {
      return p;
    }
  };

  //============================================================================
  // When indexing on _(a, b) with an extremum, return the current offset
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , ((node_ < A0
                                      , nt2::tag::relative_colon_
                                      , boost::mpl::long_<1>
                                      ,nt2::container::domain>
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& i, const A1& b, const A2& s, const A3& p, const A4&) const
    {
      return  details::
              unity_colon_value ( boost::proto::
                                  value(boost::proto::child_c<0>(i)).lower(b,s)
                                , p
                                , meta::as_<result_type>()
                                ) - (typename meta::scalar_of<result_type>::type)b;
    }
  };

  //============================================================================
  // When indexing on _(a, s, b) with an extremum, return the current offset
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , ((node_ < A0
                                      , nt2::tag::relative_colon_
                                      , boost::mpl::long_<2>
                                      ,nt2::container::domain>
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& i, const A1& b, const A2& s, const A3& p, const A4&) const
    {
      return  details::
              colon_value ( boost::proto::
                            value(boost::proto::child_c<0>(i)).lower(b,s)
                          , boost::proto::value(boost::proto::child_c<1>(i))
                          , p
                          , meta::as_<result_type>()
                          ) - (typename meta::scalar_of<result_type>::type)b;
    }
  };

  //============================================================================
  // When indexing begin_/end_ +/- i, evaluate to proper extremum
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)(A3)(A4)
                            , ((expr_ < extremum_< A0 >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (generic_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& idx, const A1&, const A2& sz, const A3&, const A4&) const
    {
      return nt2::splat<result_type>(boost::proto::value(idx).index(0u,sz));
    }
  };

} }

#endif
