//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_PLANEROT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_PLANEROT_HPP_INCLUDED

#include <nt2/linalg/functions/planerot.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of planerot is called whenever a tie(...) = planerot(...) is captured
  // before assign is resolved. As a tieable function, planerot retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::planerot_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::planerot_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          dest0_t;
    typedef typename dest0_t::value_type                                value_t;
    typedef nt2::table<value_t>                                           tab_t;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {

      child0& rot(boost::proto::child_c<0>(a1));
      rot = nt2::eye(of_size(2, 2), meta::as_<value_t>());
      const value_t x1 = boost::proto::child_c<0>(a0)(first_index<1>(boost::proto::child_c<0>(a0)));
      const value_t x2 = boost::proto::child_c<0>(a0)(last_index<1>(boost::proto::child_c<0>(a0)));
      value_t r = nt2::hypot(x1, x2);
      if (x2)
      {
        rot(1, 1) = rot(2, 2) = x1;
        rot(1, 2) = x2;
        rot(2, 1) =  -rot(1, 2);
        rot *= nt2::rec(r);
      }
      results(r, a1, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    // potentially fills the second arg out
    //==========================================================================
    BOOST_FORCEINLINE
      void results(const value_t, A1 &, boost::mpl::long_<1> const&) const{}

    BOOST_FORCEINLINE
      void results(const value_t r, A1 & a1, boost::mpl::long_<2> const&) const
    {
      tab_t y(of_size(2, 1));
      y(1) = r; y(2) = nt2::Zero<value_t>();
      boost::proto::child_c<1>(a1) = y;
    }

  };
} }

#endif
