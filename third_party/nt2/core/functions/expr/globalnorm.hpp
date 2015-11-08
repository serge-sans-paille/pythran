/*******************************************************************************
 *         Copyright 2003-2014 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_EXPR_GLOBALNORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_GLOBALNORM_HPP_INCLUDED

#include <nt2/include/functions/globalnorm.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/globalnormp.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/tags.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  // Default globalnorm is globalnorm2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnorm_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const &a0)
                          , nt2::globalnorm2(a0)
                          );
  };

  // Selects globalnorm from dynamic norm value
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnorm_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
                           )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 a1) const
    {
      BOOST_ASSERT_MSG( (a1 > 0) || (a1 == Minf<A1>())
                      , "p must be strictly positive or infinite"
                      );

      if(a1 == Two<A1>())  return nt2::globalnorm2(a0);
      if(a1 == One<A1>())  return nt2::globalasum1(a0);
      if(a1 == Inf<A1>())  return nt2::globalmax(nt2::abs(a0));
      if(a1 == Minf<A1>()) return nt2::globalmin(nt2::abs(a0));

      return nt2::globalnormp(a0, a1);
    }
  };

  // Selects globalnorm from static norm value
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnorm_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (mpl_integral_< scalar_< fundamental_<A1> > >)
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG( (A1::value > 0), "p must be strictly positive" );
      return eval(a0, a1);
    }

    template<int Value>
    BOOST_FORCEINLINE result_type eval( A0 const &a0
                                      , boost::mpl::int_<Value> const&
                                      ) const
    {
      return nt2::globalnormp(a0, Value);
    }

    BOOST_FORCEINLINE result_type eval( A0 const &a0
                                      , boost::mpl::int_<1> const&
                                      ) const
    {
      return nt2::globalasum1(a0);
    }

    BOOST_FORCEINLINE result_type eval( A0 const &a0
                                      , boost::mpl::int_<2> const&
                                      ) const
    {
      return nt2::globalnorm2(a0);
    }
  };

  // Selects globalnorm from static norm value tag
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnorm_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (target_<unspecified_<A1> >)
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 const&) const
    {
      return eval(a0, typename A1::type());
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::Inf const&) const
    {
      return nt2::globalmax(nt2::abs(a0));
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::Minf const&) const
    {
      return nt2::globalmin(nt2::abs(a0));
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::One const&) const
    {
      return nt2::globalasum1(a0);
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::Two const&) const
    {
      return nt2::globalnorm2(a0);
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::inf_ const&) const
    {
      return nt2::globalmax(nt2::abs(a0));
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::minf_ const&) const
    {
      return nt2::globalmin(nt2::abs(a0));
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::one_ const&) const
    {
      return nt2::globalasum1(a0);
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::two_ const&) const
    {
      return nt2::globalnorm2(a0);
    }

    BOOST_FORCEINLINE result_type eval(A0 const &a0, tag::fro_ const&) const
    {
      return nt2::globalnorm2(a0);
    }

    template<typename Tag>
    BOOST_FORCEINLINE result_type eval(A0 const &a0, Tag const&) const
    {
      // outside of Inf,  Minf,  One and Two we get back to the dynamic normp
      typename boost::dispatch::make_functor<Tag,A0>::type callee;
      type_t value = callee( nt2::meta::as_<type_t>() );

      BOOST_ASSERT_MSG( value > 0, "Norm value must be strictly positive" );
      return  globalnormp(a0, value);
    }
  };
} }

#endif


