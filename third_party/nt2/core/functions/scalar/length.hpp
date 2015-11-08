//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_LENGTH_HPP_INCLUDED

#include <nt2/core/functions/length.hpp>
#include <nt2/core/functions/length.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::length_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::length_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    // See if the numel is somehow statically 0
    typedef typename boost::dispatch::meta::call<tag::numel_(A0)>::type numel_t;
    typedef typename mpl_value<numel_t>::type                           empty_t;

    typedef typename  boost::dispatch::make_functor<tag::max_,A0>::type func_t;
    typedef typename  boost::fusion::result_of::front<A0>::type          first;
    typedef boost::fusion::result_of::fold<A0,first,func_t>           fusion_t;

    typedef typename  boost::mpl::eval_if_c < empty_t::value == 0
                                            , boost::mpl::size_t<0U>
                                            , fusion_t
                                            >::type                result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return eval( a0, boost::mpl::int_<empty_t::value>() );
    }

    BOOST_FORCEINLINE result_type eval(const A0&, boost::mpl::int_<0> const&) const
    {
      return result_type();
    }

    template<int N>
    BOOST_FORCEINLINE result_type eval(const A0& a0, boost::mpl::int_<N> const&) const
    {
      return boost::fusion::fold( a0
                                , boost::fusion::front(a0)
                                , func_t()
                                );
    }

    BOOST_FORCEINLINE result_type eval(const A0& a0, boost::mpl::int_<-1> const&) const
    {
      return numel(a0) ? eval(a0,boost::mpl::int_<1>()) : 0u;
    }
  };
} }

#endif
