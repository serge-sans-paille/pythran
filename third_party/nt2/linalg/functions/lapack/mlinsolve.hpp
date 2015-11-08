//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_MLINSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_MLINSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/mlinsolve.hpp>
#include <nt2/include/functions/clinsolve.hpp>
#include <nt2/include/functions/gemsv.hpp>
#include <nt2/include/functions/mcsne.hpp>
#include <nt2/include/functions/pomsv.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/proto/traits.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mlinsolve_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>)) // A
                              ((ast_<A1, nt2::container::domain>)) // B
                              ((ast_<A2, nt2::container::domain>)) // X
                            )
  {
    typedef void  result_type;;
    typedef typename A0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D,shape)> desired_semantic1;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D)> desired_semantic;
    typedef nt2::container::table<ctype_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2& a2 ) const
    {
      const type_t x = type_t(0);
      eval(a0,a1,a2,x,shape());
    }
    //==========================================================================
    /// INTERNAL ONLY - Shape analysis

    /// INTERNAL ONLY - Rectangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2& a2, double const, nt2::rectangular_ const&) const
    {
      nt2_la_int m   = boost::fusion::at_c<0>( a0.extent() );
      nt2_la_int n   = boost::fusion::at_c<1>( a0.extent() );
      nt2_la_int nb   = boost::fusion::at_c<1>( a1.extent() );

      if (m>n)
      {
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);

      a2 = nt2::mcsne(a,b);
      }
      else
      {
      // Copy of matrix a is costly and should be avoided
      matrix_type entry(a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      a2.resize(nt2::of_size(m,nb));
      nt2_la_int iter = nt2::gemsv(boost::proto::value(entry)
                       ,boost::proto::value(b),boost::proto::value(a2) );
      boost::dispatch::ignore_unused(iter);
      }

    }

    /// INTERNAL ONLY - Positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2& a2, double const, nt2::positive_definite_ const&) const
    {
      nt2_la_int m   = boost::fusion::at_c<0>( a0.extent() );
      nt2_la_int n   = boost::fusion::at_c<1>( a1.extent() );

      matrix_type entry(a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      a2.resize(nt2::of_size(m,n));
      nt2_la_int iter = nt2::pomsv( boost::proto::value(entry)
                                  , boost::proto::value(b),a2);
      boost::dispatch::ignore_unused(iter);
    }

    /// INTERNAL ONLY - Default case
    template<typename T, typename sh> BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2& a2, T const, sh const&) const
    {
      nt2::clinsolve(a0,a1,nt2::tie(a2));
    }

  };


} }


#endif
