//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_COLON_HPP_INCLUDED

#include <nt2/core/functions/colon.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/constants/threeeps.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/core/functions/details/colon.hpp>
#include <nt2/include/functions/scalar/fuzzy_equal.hpp>
#include <nt2/include/functions/scalar/tolerant_floor.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Generates colon from a pair of [low,up]
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::common_type<A0,A1>::type          base_t;
    typedef meta::constant_<nt2::tag::unity_colon_,base_t> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colon_
                                          , container::domain
                                          , of_size_<1, -1>
                                          , constant_t
                                          , meta::as_<base_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A1 const& u) const
    {
      return  boost::proto::
              make_expr < nt2::tag::colon_
                        , container::domain
                        > ( of_size_<1, -1>(1,details::unity_colon_size(l,u))
                          , constant_t(l)
                          , meta::as_<base_t>()
                          );
    }
  };

  /// INTERNAL ONLY
  /// Generates colon from a pair of [low,up] (static)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)
                            , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                              (mpl_integral_< scalar_< arithmetic_<A1> > >)
                           )
  {
    static const std::size_t sz = (A1::value>=A0::value)
                                ? std::size_t(A1::value-A0::value+1) : 0u;

    typedef typename boost::common_type<typename A0::value_type, typename A1::value_type>::type base_t;
    typedef meta::constant_<nt2::tag::unity_colon_,base_t> constant_t;

    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colon_
                                          , container::domain
                                          , of_size_<1, sz>
                                          , constant_t
                                          , meta::as_<base_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l, A1 const&) const
    {
      return  boost::proto::
              make_expr < nt2::tag::colon_
                        , container::domain
                        > ( of_size_<1, sz>()
                          , constant_t(l)
                          , meta::as_<base_t>()
                          );
    }
  };

  /// INTERNAL ONLY
  ///  Generates colon from a pair of [low,up] and a step
  /// Easy case : everything is signed integral
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename boost::common_type<A0,A1,A2>::type                 base_t;
    typedef meta::constant_<nt2::tag::colon_,base_t>                constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colon_
                                          , container::domain
                                          , of_size_<1, -1>
                                          , constant_t
                                          , meta::as_<base_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      return  boost::proto::
              make_expr < nt2::tag::colon_
                        , container::domain
                        > ( of_size_<1,-1>(1,details::colon_size(l,s,u))
                          , constant_t(l,s)
                          , meta::as_<A0>()
                          );
    }
  };

  //============================================================================
  // Generates colon from a pair of [low,up] and a number of elements
  // Not easy case : floating points :s
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::colon_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0,A1,A2>::type base_t;
    typedef meta::constant_<nt2::tag::colon_,base_t>                constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::colon_
                                          , container::domain
                                          , of_size_<1, -1>
                                          , constant_t
                                          , meta::as_<base_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& s, A2 const& u) const
    {
      std::size_t n = (s) ? (((u-l)*s >= 0) ? size(l,s,u) : 0)
                          : std::size_t(u);

      return boost::proto::make_expr< nt2::tag::colon_
                                    , container::domain
                                    > ( of_size_<1, -1>(1,n)
                                      , constant_t(l,s)
                                      , meta::as_<base_t>()
                                      );
    }

    BOOST_FORCEINLINE std::size_t
    size(A0 const& l, A1 const& s, A2 const& u) const
    {
      const std::size_t nelt  = std::size_t(tolerant_floor(base_t(u-l+s)/base_t(s)));
      const base_t      eps3  = Threeeps<base_t>();

      if(!fuzzy_equal(l+base_t(nelt-1)*s, u, eps3))
      {
              if(fuzzy_equal(l+base_t(nelt-2)*s, u, eps3))  return nelt-1;
        else  if(fuzzy_equal(l+base_t(nelt)*s  , u, eps3))  return nelt+1;
      }
      return nelt;
    }
  };
} }

#endif
