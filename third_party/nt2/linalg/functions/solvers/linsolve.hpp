//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SOLVERS_LINSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SOLVERS_LINSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/linsolve.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/clinsolve.hpp>
#include <nt2/include/functions/plinsolve.hpp>
#include <nt2/include/functions/mlinsolve.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // LINSOLVE
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linsolve_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::linsolve_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type     type_t;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      eval(a0,a1,N0(),N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B)
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      const type_t x = type_t(0);
      solve_sqr(a0,a1,nt2::policy<ext::classic_>(),x);
    }

    //==========================================================================
    /// INTERNAL ONLY - X-R = LINSOLVE(A,B)
    template<typename N> BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , N const&
              , boost::mpl::long_<2> const&
              ) const
    {
      nt2::plinsolve( boost::proto::child_c<0>(a0) // A
                    , boost::proto::child_c<1>(a0) // B
                    , nt2::tie( boost::proto::child_c<0>(a1)
                              , boost::proto::child_c<1>(a1) )
                    );
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B,opts) - Matrix must be square here
    /// test for matlab type opts(shape structure)
    /// add a dispatch case for solve_sqr
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      const type_t x = type_t(0);
      solve_sqr(a0,a1,boost::proto::value(boost::proto::child_c<2>(a0)),x);
    }
    //==========================================================================
    /// INTERNAL ONLqY - X = LINSOLVE(A,B,opts) with sv or gelsy
    BOOST_FORCEINLINE
    void solve_sqr(A0 const& a0, A1 const& a1 ,nt2::policy<ext::classic_> const&
                  , type_t const ) const
    {
      nt2::clinsolve( boost::proto::child_c<0>(a0)           // A
                    , boost::proto::child_c<1>(a0)           // B
                    , nt2::tie(boost::proto::child_c<0>(a1)) // X
                    );
    }

    /// INTERNAL ONLY - X = LINSOLVE(A,B,opts) with svx
    BOOST_FORCEINLINE
    void solve_sqr(A0 const& a0, A1 const& a1,nt2::policy<ext::precise_> const&
                  , type_t const ) const
    {
      nt2::plinsolve( boost::proto::child_c<0>(a0) // A
                    , boost::proto::child_c<1>(a0) // B
                    , nt2::tie(boost::proto::child_c<0>(a1) ) // X
                    );
    }

    /// INTERNAL ONLY - X = LINSOLVE(A,B,opts) with dsgesv or dsposv
    BOOST_FORCEINLINE
    void solve_sqr(A0 const& a0, A1 const& a1,nt2::policy<ext::fast_> const&
                  , double const ) const
    {
      nt2::mlinsolve( boost::proto::child_c<0>(a0) // A
                    , boost::proto::child_c<1>(a0) // B
                    , boost::proto::child_c<0>(a1) // X
                    );
    }


    /// INTERNAL ONLY - X = LINSOLVE(A,B,opts) with dsgesv or dsposv
    BOOST_FORCEINLINE
    void solve_sqr(A0 const& a0, A1 const& a1,nt2::policy<ext::fast_> const&
                  , float const x ) const
    {
      solve_sqr(a0,a1,nt2::policy<ext::classic_>(),x);
    }

  };
} }

#endif
