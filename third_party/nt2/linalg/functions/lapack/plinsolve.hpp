//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_PLINSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_PLINSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/plinsolve.hpp>
#include <nt2/include/functions/gesvx.hpp>
#include <nt2/include/functions/sysvx.hpp>
#include <nt2/include/functions/clinsolve.hpp>
#include <nt2/include/functions/posvx.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/linalg/functions/details/eval_linsolve.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::plinsolve_, tag::cpu_
                            , (A0)(A1)(A2)(N2)
                            , ((ast_<A0, nt2::container::domain>))  // A
                              ((ast_<A1, nt2::container::domain>))  // B
                              ((node_<A2, nt2::tag::tie_             // X-R
                                    , N2, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename A0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D)> desired_semantic;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D,shape)> desired_semantic1;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2 const&  a2 ) const
    {
      eval(a0,a1,a2,N2(),shape());
    }

    //==========================================================================
    /// INTERNAL ONLY - Shape analysis

    /// INTERNAL ONLY - X = LINSOLVE(A,B) -- Rectangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<1> const
              , nt2::rectangular_ const&) const
    {
      type_t rcond;
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2::gesvx( boost::proto::value(a), boost::proto::value(b)
              , boost::proto::value(boost::proto::child_c<0>(a2)), rcond );
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- Rectangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<2> const
              , nt2::rectangular_ const&) const
    {
      type_t rcond;
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2::gesvx( boost::proto::value(a), boost::proto::value(b)
              , boost::proto::value(boost::proto::child_c<0>(a2))
              , rcond );
      boost::proto::child_c<1>(a2) = rcond;
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) -- symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<1> const
              , nt2::symmetric_ const&) const
    {
      type_t rcond;
      nt2::container::table<nt2_la_int> piv(nt2::of_size(a0.leading_size(),1));
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2_la_int iter = nt2::sysvx( boost::proto::value(a),boost::proto::value(piv)
                                 , boost::proto::value(b)
                                 , boost::proto::value(boost::proto::child_c<0>(a2))
                                 , rcond);
      boost::dispatch::ignore_unused(iter);
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<2> const
              , nt2::symmetric_ const&) const
    {
      type_t rcond;
      nt2::container::table<nt2_la_int> piv(nt2::of_size(a0.leading_size(),1));
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2_la_int iter = nt2::sysvx( boost::proto::value(a),boost::proto::value(piv)
                                 , boost::proto::value(b)
                                 , boost::proto::value(boost::proto::child_c<0>(a2))
                                 , rcond);

      boost::dispatch::ignore_unused(iter);
      boost::proto::child_c<1>(a2) = rcond;
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) -- positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<1> const
              , nt2::positive_definite_ const&) const
    {
      type_t rcond;
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2_la_int iter = nt2::posvx( boost::proto::value(a), boost::proto::value(b)
                                  , boost::proto::value(boost::proto::child_c<0>(a2))
                                  , rcond);
      boost::dispatch::ignore_unused(iter);
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2 ,boost::mpl::long_<2> const
              , nt2::positive_definite_ const&) const
    {
      type_t rcond;
      boost::proto::child_c<0>(a2).resize(nt2::of_size(a0.leading_size(),1));
      NT2_AS_TERMINAL_IN(desired_semantic1,a,a0);
      NT2_AS_TERMINAL_IN(desired_semantic,b,a1);
      nt2_la_int iter = nt2::posvx( boost::proto::value(a), boost::proto::value(b)
                                  , boost::proto::value(boost::proto::child_c<0>(a2))
                                  , rcond);

      boost::dispatch::ignore_unused(iter);
      boost::proto::child_c<1>(a2) = rcond;
    }

    /// INTERNAL ONLY - No info on this shape
    template<typename N,typename sh>
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1, A2 const& a2, N const&, sh const&) const
    {
      nt2::clinsolve(a0,a1,a2);
    }

  };


} }


#endif
