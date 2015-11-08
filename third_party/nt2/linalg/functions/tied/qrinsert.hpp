//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_QRINSERT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_QRINSERT_HPP_INCLUDED

#include <nt2/linalg/functions/qrinsert.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/planerot.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = qrinsert(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qrinsert_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qrinsert_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      char orient =  choice(a0, N0());
      insert(a0, a1, orient, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
    char choice(A0 const &, boost::mpl::long_<4> const &) const
    {
      return 'c';
    }

    BOOST_FORCEINLINE
    char choice(A0 const & a0, boost::mpl::long_<5> const &) const
    {
      return boost::proto::value(boost::proto::child_c<4>(a0));
    }


    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
    void insert(A0& a0, A1 & a1, const char& orient, boost::mpl::long_<1> const&) const
    {
      table<value_t> r1;
      BOOST_AUTO_TPL(q1, boost::proto::child_c<0>(a1));
      do_it(a0,orient,q1,r1);
    }

    BOOST_FORCEINLINE
    void insert(A0& a0, A1 & a1, const char& orient, boost::mpl::long_<2> const&) const
    {
      BOOST_AUTO_TPL(r1, boost::proto::child_c<1>(a1));
      BOOST_AUTO_TPL(q1, boost::proto::child_c<0>(a1));
      do_it(a0,orient,q1,r1);
    }

    template < class Q1, class R1>  BOOST_FORCEINLINE
    void do_it(A0& a0, const char& orient, Q1 & q1,  R1 & r1) const
    {
      BOOST_AUTO_TPL(q,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(r,  boost::proto::child_c<1>(a0));
      size_t j =         boost::proto::child_c<2>(a0);
      BOOST_AUTO_TPL(x,  boost::proto::child_c<3>(a0));
      table<value_t, nt2::of_size_<2, 2> >  g;
      size_t n = size(r, 2);
      size_t m = size(r, 1);
      if (orient == 'c')
      {
        // Make room and insert x before j-th column.
        r1.resize(nt2::of_size(m, n+1));
        q1 = q;
        r1(nt2::_,nt2::_(1, j-1))  = r(nt2::_,nt2::_(1, j-1));
        r1(nt2::_,nt2::_(j+1, n+1)) = r(nt2::_,nt2::_(j, n));
        r1(nt2::_,j) = nt2::mtimes(nt2::ct(q), x);
        ++n;
        //  now r has nonzeros below the diagonal in the j-th column,
        //  and "extra" zeros on the diagonal in later columns.
        //     r = [x x x x x         [x x x x x
        //          0 x x x x    g     0 x x x x
        //          0 0 + x x   --->   0 0 * * *
        //          0 0 + 0 x          0 0 0 * *
        //          0 0 + 0 0]         0 0 0 0 *]
        //  use givens rotations to zero the +'s, one at a time, from bottom to top.
        //
        //  q is treated to (the transpose of) the same rotations.
        //     q = [x x x x x    g'   [x x * * *
        //          x x x x x   --->   x x * * *
        //          x x x x x          x x * * *
        //          x x x x x          x x * * *
        //          x x x x x]         x x * * *]
         for(size_t k = m-1; k >= j; --k)
         {
           BOOST_AUTO_TPL(p, nt2::cons(k, k+1));
           nt2::tie(g,r1(p,j)) = nt2::planerot(r1(p,j));
           if (k < n)
           {
             r1(p,nt2::_(k+1, n)) = nt2::mtimes(g, r1(p,nt2::_(k+1, n)));
           }
           q1(nt2::_,p) = nt2::mtimes(q1(nt2::_,p), nt2::ct(g));
         }

      }
      else
      {
        r1 = catv(x, r);
        q1 = catv(cath(nt2::One<value_t>(), nt2::zeros(1,m,meta::as_<value_t>())),
                  cath(nt2::zeros(m,1,meta::as_<value_t>()),q));
        //  now r is upper hessenberg.
        //     r = [x x x x         [* * * *
        //          + x x x    g       * * *
        //            + x x   --->       * *
        //              + x                *
        //                +          0 0 0 0
        //          0 0 0 0          0 0 0 0
        //          0 0 0 0]         0 0 0 0]
        //  use givens rotations to zero the +'s, one at a time, from top to bottom.
        //
        //  q is treated to (the transpose of) the same rotations and then a row
        //  permutation, p, to shuffle row 1 down to row j.
        //     q = [1 | 0 0 0 0 0         [# # # # # #         [* * * * * *
        //          --|----------          -----------          -----------
        //          0 | x x x x x    g'    * * * * * *    p     * * * * * *
        //          0 | x x x x x   --->   * * * * * *   --->   # # # # # #
        //          0 | x x x x x          * * * * * *          * * * * * *
        //          0 | x x x x x          * * * * * *          * * * * * *
        //          0 | x x x x x]         * * * * * *]         * * * * * *]

        for(size_t i = 1; i <= nt2::min(m,n); ++i)
        {
          BOOST_AUTO_TPL(p, nt2::cons(i, i+1));
          nt2::tie(g,r1(p,i)) = nt2::planerot(r1(p,i));
          r1(p,nt2::_(i+1, n)) = nt2::mtimes(g, r1(p,nt2::_(i+1, n)));
          q1(nt2::_,p) = nt2::mtimes(q1(nt2::_,p), nt2::ct(g));
        }
        // this permutes row 1 of q*r to row j of q(p,:)*r
        if (j != 1)
        {
          BOOST_AUTO_TPL(p, nt2::cath(nt2::cath(nt2::_(size_t(2), j), size_t(1)), nt2::_(j+1, m+1)));
          table<value_t> qq = q1(p,nt2::_);
          q1 = qq;
        }


      }
    }

  };
} }

#endif

