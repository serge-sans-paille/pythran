//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_RREF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_RREF_HPP_INCLUDED

#include <nt2/linalg/functions/rref.hpp>
#include <nt2/linalg/functions/factorizations/rref.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <cstring>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of rref is called whenever a tie(...) = rref(...) is captured
  // before assign is resolved. As a tieable function, rref retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rref_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::rref_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          dest0_t;
    typedef typename dest0_t::value_type                             value_type;
    typedef typename meta::
            call< nt2::tag::
                  factorization::rref_(child0, value_type, nt2::ext::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      // Retrieve the tol options
      value_type tol = choice(a0, N0());

      // Factorize in place
      fact_t f = factorization::rref(boost::proto::child_c<0>(a1),tol,nt2::in_place_);
      decomp(f, a1, N1());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // get tol
    //==========================================================================
    BOOST_FORCEINLINE
    value_type choice(A0 const &, boost::mpl::long_<1> const &) const
    {
      return Mone<value_type>();
    }

    BOOST_FORCEINLINE
    value_type choice(A0 const & a0, boost::mpl::long_<2> const &) const
    {
      return boost::proto::value(boost::proto::child_c<1>(a0));
    }
    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.rref();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t const& f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.rref();
      boost::proto::child_c<1>(a1) = f.jb();
    }

  };
} }

#endif
