//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_COLON_HPP_INCLUDED

#include <nt2/core/functions/colon.hpp>
#include <nt2/core/container/extremum/category.hpp>
#include <nt2/core/functions/details/colon.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates colon from a pair of [low,begin_/end_+offset]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (extremum_<A1>)
                            )
  {
    typedef typename meta::strip<A0>::type          base_t;
    typedef typename meta::strip<A1>::type          ext_t;
    typedef details::relative_colon<base_t, ext_t>  relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A1 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr<tag::relative_colon_, container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [begin_/end_+offset, upper]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)
                            , (extremum_<A0>)
                              (scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename meta::strip<A0>::type          ext_t;
    typedef typename meta::strip<A1>::type          base_t;
    typedef details::relative_colon<ext_t, base_t>  relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A1 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr<tag::relative_colon_, container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [begin_/end_+offset, begin_/end_+offset]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)
                            , (extremum_<A0>)
                              (extremum_<A1>)
                            )
  {
    typedef typename meta::strip<A0>::type          ext0_t;
    typedef typename meta::strip<A1>::type          ext1_t;
    typedef details::relative_colon<ext0_t,ext1_t>  relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A1 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr<tag::relative_colon_, container::domain>(that);
    }
  };

  //============================================================================
  // Generates colon from a pair of [low,step,begin_/end_+offset]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                              (extremum_<A2>)
                            )
  {
    typedef typename boost::common_type<A0,A1>::type  base_t;
    typedef typename meta::strip<A2>::type            ext_t;
    typedef details::relative_colon<base_t, ext_t>    relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                , base_t
                                >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr < tag::relative_colon_
                        , container::domain
                        > ( that
                          , base_t(s)
                          );
    }
  };

  //============================================================================
  // Generates colon from a pair of [begin_/end_+offset,step,upper]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (extremum_<A0>)
                              (scalar_< arithmetic_<A1> >)
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename meta::strip<A0>::type            ext_t;
    typedef typename boost::common_type<A1,A2>::type  base_t;
    typedef details::relative_colon<ext_t,base_t>    relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                , base_t
                                >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr < tag::relative_colon_
                        , container::domain
                        > ( that
                          , base_t(s)
                          );
    }
  };

  //============================================================================
  // Generates colon from a pair of [begin_/end_+offset,step,upper]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (extremum_<A0>)
                              (scalar_< arithmetic_<A1> >)
                              (extremum_<A2>)
                            )
  {
    typedef typename meta::strip<A0>::type            ext0_t;
    typedef typename meta::strip<A2>::type            ext1_t;
    typedef details::relative_colon<ext0_t, ext1_t>   relative_t;

    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::relative_colon_
                                , container::domain
                                , relative_t
                                , typename meta::strip<A1>::type
                                >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      relative_t that = {l,u};
      return  boost::proto::
              make_expr < tag::relative_colon_
                        , container::domain
                        > ( that
                          , s
                          );
    }
  };
} }

#endif
