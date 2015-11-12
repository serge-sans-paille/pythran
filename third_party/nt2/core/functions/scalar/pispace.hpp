//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_PISPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_PISPACE_HPP_INCLUDED

#include <nt2/core/functions/pispace.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/exp10.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/pispace.hpp>
#include <nt2/include/functions/scalar/splat.hpp>
#include <nt2/include/functions/scalar/enumerate.hpp>
#include <nt2/include/constants/log10_pi.hpp>

//==============================================================================
// pispace actual functor forward declaration
//==============================================================================
namespace nt2 { namespace details { template<class T> struct pispace; } }

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates pispace from a pair of [low,up]
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pispace_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pispace_
                                          , container::domain
                                          , of_size_<1,50>
                                          , nt2::details::pispace<A0>
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& l) const
    {
      return  boost::proto::
              make_expr < nt2::tag::pispace_
                        , container::domain
                        > ( of_size_<1,50>()
                          , nt2::details::pispace<A0>(l,50)
                          , meta::as_<A0>()
                          );
    }
  };

  //============================================================================
  // Generates pispace from a pair of [low,up] and a number of elements
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pispace_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pispace_
                                          , container::domain
                                          , _2D
                                          , nt2::details::pispace<A0>
                                          , meta::as_<A0>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& l, A1 const& n) const
    {
      return  boost::proto::
              make_expr < nt2::tag::pispace_
                        , container::domain
                        > ( of_size(1,n)
                            , nt2::details::pispace<A0> (  l
                                                        , (n<2 ? 2 : n)
                                                        )
                          , meta::as_<A0>()
                          );
    }
  };
} }

namespace nt2 { namespace details
{
  //============================================================================
  // pispace actual functor : precompute step and just iterate over
  //============================================================================
  template<class T> struct pispace
  {
    pispace() {}
    pispace( T const& l, std::size_t n )
      : lower_(l), step_((Log10_pi<T>()-l)/(n-1)) {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;

      return nt2::exp10(nt2::fma ( nt2::enumerate<type>(p)
                                   , nt2::splat<type>(step_)
                                   , nt2::splat<type>(lower_)
                                   ));
    }

    T lower_, step_;
  };
} }

#endif

