//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // run tie(...) does nothing (doesn't make sense to evaluate it)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(N0)
                            , ((node_<A0, nt2::tag::tie_, N0, nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  // when storing a fusion sequence in a tie(...), run each element of the
  // sequence in its output argument
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(N0)(State)(Data)
                            , ((node_<A0, nt2::tag::tie_, N0, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (fusion_sequence_<Data>)
                            )
  {
    typedef A0& result_type;

    struct impl
    {
      BOOST_FORCEINLINE impl(A0& a0_, State const& state_, Data const& data_)
                            : a0(a0_), state(state_), data(data_)
      {
      }

      template<int I>
      void operator()() const
      {
        nt2::run(boost::proto::child_c<I>(a0), state, boost::fusion::at_c<I>(data));
      }

      A0& a0;
      State const& state;
      Data const& data;
      private:
      impl& operator=(impl const&);
    };

    BOOST_FORCEINLINE result_type operator()(A0& a0, State const& state, Data const& data) const
    {
      boost::simd::meta::iterate<N0::value>(impl(a0, state, data));
      return a0;
    }
  };

  //============================================================================
  // when reading a fusion sequence from a tie(...), run each element of the
  // sequence and store it in another sequence
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(N0)(State)(Data)
                            , ((node_<A0, nt2::tag::tie_, N0, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (target_< fusion_sequence_<Data> >)
                            )
  {
    typedef typename Data::type result_type;

    struct impl
    {
      BOOST_FORCEINLINE impl(A0& a0_, State const& state_, result_type& data_)
                            : a0(a0_), state(state_), data(data_)
      {
      }

      template<int I>
      void operator()() const
      {
        boost::fusion::at_c<I>(data) = nt2::run( boost::proto::child_c<I>(a0)
                                               , state
                                               , boost::dispatch::meta::
                                                 as_< typename boost::fusion::result_of::
                                                      value_at_c<result_type, I>::type
                                                    >()
                                               );
      }

      A0& a0;
      State const& state;
      result_type& data;
      private:
      impl& operator=(impl const&);
    };

    BOOST_FORCEINLINE result_type operator()(A0& a0, State const& state, Data const&) const
    {
      result_type data;
      boost::simd::meta::iterate<N0::value>(impl(a0, state, data));
      return data;
    }
  };

  //============================================================================
  // when storing a fusion sequence in a terminal, take first element
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::terminal_, tag::cpu_
                            , (A0)(N0)(State)(Data)
                            , ((node_<A0, nt2::tag::terminal_, N0, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (fusion_sequence_<Data>)
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, State const& state, Data const& data) const
    {
      nt2::run(a0, state, boost::fusion::at_c<0>(data));
      return a0;
    }
  };

  //============================================================================
  // Call function for tie(...) = tieable_func(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, nt2::tag::tie_, N0, nt2::container::domain>))
                              ((node_<A1, tieable_<T1>, N1, nt2::container::domain>))
                            )
  {
    typedef A0&                                         result_type;
    typedef typename boost::proto::tag_of<A1>::type     tag_t;
    typedef typename make_functor<tag_t,A0>::type       func_t;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      func_t callee;
      callee(a1, a0);

      return a0;
    }
  };

  //============================================================================
  // Handles elementwise  = tieable_func(...) by transforming it to
  //     tie(elementwise) = tieable_func(...)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::assign_, tag::cpu_
                              , (A0)(T0)(N0)(A1)(T1)(N1)
                              , (mpl::not_< is_same<T0, nt2::tag::tie_> >)
                              , ((node_ <A0, elementwise_<T0>, N0 ,nt2::container::domain> ))
                                ((node_ <A1, tieable_<T1>, N1,nt2::container::domain>))
                              )
  {
    typedef typename meta::call<tag::tie_(A0&)>::type tied;
    typedef typename meta::call<tag::assign_(tied, A1&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      return nt2::assign(nt2::tie(a0), a1);
    }
  };
} }

#endif
