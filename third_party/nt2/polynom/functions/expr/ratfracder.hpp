//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_RATFRACDER_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_RATFRACDER_HPP_INCLUDED

#include <nt2/polynom/functions/ratfracder.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/polyder.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/tie.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  //============================================================================
  // This version of ratfracder is called whenever a tie(...) = ratfracder(...) is captured
  // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ratfracder_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::ratfracder_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename A0::value_type                                  value_type;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      val(a0, a1, N1(), N0());
    }

  private:
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<2> const &, boost::mpl::long_<2> const &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       n_type;
      typedef typename boost::proto::result_of::child_c<A1&,1>::type       d_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::type       a_type;
      typedef typename boost::proto::result_of::child_c<A0&,1>::type       b_type;
      a_type a = boost::proto::child_c<0>(a0);
      b_type b = boost::proto::child_c<1>(a0);
      n_type n = boost::proto::child_c<0>(a1);
      d_type d = boost::proto::child_c<1>(a1);
      _2D sizee;
      n.resize(extent(a0));
      n = nt2::conv(nt2::polyder(a),b)-nt2::conv(nt2::polyder(b),a);
      sizee[0] = 1;
      sizee[1] = numel(b);
      sizee[1] = sizee[1] ? 2*sizee[1]-1:0;
      d.resize(sizee);
      d = nt2::conv(b, b);
    }
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<1> const &, boost::mpl::long_<2> const &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       n_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::type       a_type;
      typedef typename boost::proto::result_of::child_c<A0&,1>::type       b_type;
      a_type a = boost::proto::child_c<0>(a0);
      b_type b = boost::proto::child_c<1>(a0);
      n_type n = boost::proto::child_c<0>(a1);
      n = nt2::conv(nt2::polyder(a),b)-nt2::conv(nt2::polyder(b),a);
    }
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<1> const &, boost::mpl::long_<1> const &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       n_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::type       a_type;
      a_type a = boost::proto::child_c<0>(a0);
      n_type n = boost::proto::child_c<0>(a1);
      n = polyder(a);
    }
  };
} }


#endif
