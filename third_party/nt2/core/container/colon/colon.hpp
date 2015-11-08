//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED
#define NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED

#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/domain.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/core/functions/table/details/is_vectorizable_indexer.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace container
{
  //==========================================================================
  // colon_ is an helper class that handles the _ placeholders behavior
  //==========================================================================
  struct colon_
  {
    // colon_ as a sink for tie
    template<class T> colon_ const& operator=(T const&) const { return *this; }

    // _() as []
    boost::proto::result_of::
    make_expr< nt2::tag::empty_colon_, container::domain
             , of_size_<0>
             , meta::constant_<nt2::tag::unity_colon_, double>
             , meta::as_<double>
             >::type
    operator()() const
    {
      return boost::proto::make_expr< nt2::tag::empty_colon_, container::domain >
            ( of_size_<0>(), meta::constant_<nt2::tag::unity_colon_, double>(1.), meta::as_<double>() );
    }

    // colon as a:b
    template<class Begin, class End>
    typename meta::call<nt2::tag::colon_(Begin,End)>::type
    operator()(Begin b, End e) const
    {
      return nt2::colon(b,e);
    }

    // colon as a:s:b
    template<class Begin, class Step, class End>
    typename meta::call<nt2::tag::colon_(Begin,Step,End)>::type
    operator()(Begin  b, Step s, End e) const
    {
      return nt2::colon(b,s,e);
    }
  };
} }

namespace nt2
{
  //==========================================================================
  /*!
   * _ is a multi-purpose placeholder in \nt2:
   *
   *   - it acts as \matlab \c : in indexing expression
   *   - it enables \c :(b,s,e) to mimic \matlab \c b:s:e iota notation
   *   - _() is Matlab []
   *   - it acts as a sink in tie expressions
   **/
  //==========================================================================
  container::colon_ const _ = {};
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<>
  struct is_vectorizable_scalar
            < nt2::container::expression
                    < boost::proto::
                            basic_expr< boost::proto::tag::terminal
                                      , boost::proto::term<nt2::container::colon_>
                                      , 0l
                                      >
                    , nt2::container::colon_
                    >
            >
        : boost::mpl::false_
  {
  };

  /// INTERNAL ONLY
  template<class Cardinal>
  struct is_vectorizable_indexer
            < nt2::container::expression
                    < boost::proto::
                            basic_expr< boost::proto::tag::terminal
                                      , boost::proto::term<nt2::container::colon_>
                                      , 0l
                                      >
                    , nt2::container::colon_
                    >
            , Cardinal
            >
        : boost::mpl::true_
  {
  };
} }
#endif
