//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_TRAIT_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_TRAIT_TRANSFORM_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  //==============================================================================
  // Glue that creates a Proto primitive transforms that applies a given trait
  //==============================================================================
  template< template<class Tag, class Domain, int N, class Expr> class Trait
          , class Domain
          >
  struct trait_transform
      : boost::proto::transform< trait_transform<Trait, Domain> >
  {
    template<class Expr, class State, class Data>
    struct impl : boost::proto::transform_impl<Expr, State, Data>
    {
      typedef Trait< typename boost::dispatch::meta::
                     hierarchy_of< typename boost::proto::
                                   tag_of<typename impl::expr>::type
                                 >::type
                   , Domain
                   , boost::proto::arity_of<typename impl::expr>::value
                   , typename impl::expr
                   >                         function;
      typedef typename function::result_type result_type;

      BOOST_FORCEINLINE result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param
                , typename impl::data_param
                ) const
      {
        return function()(e);
      }
    };
  };
} }

#endif
