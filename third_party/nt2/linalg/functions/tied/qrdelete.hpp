//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_QRDELETE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_QRDELETE_HPP_INCLUDED

#include <nt2/linalg/functions/qrdelete.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/planerot.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = qrdelete(...) at assign time and resolve to optimized call
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qrdelete_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qrdelete_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef table<value_t, _2D>                                           tab_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      char orient =  choice(a0, N0());
      del(a0, a1, orient, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    BOOST_FORCEINLINE
    char choice(A0 const &, boost::mpl::long_<3> const &) const
    {
      return 'c';
    }

    BOOST_FORCEINLINE
    char choice(A0 const & a0, boost::mpl::long_<4> const &) const
    {
      return boost::proto::value(boost::proto::child_c<3>(a0));
    }


    //==========================================================================
    // INTERNAL ONLY
    // fill the args out
    //==========================================================================
    BOOST_FORCEINLINE
    void del(A0& a0, A1 & a1, const char& orient, boost::mpl::long_<1> const&) const
    {
      tab_t r1;
      BOOST_AUTO_TPL(q1, boost::proto::child_c<0>(a1));
      do_it(a0,orient,q1,r1);
    }

    BOOST_FORCEINLINE
    void del(A0& a0, A1 & a1, const char& orient, boost::mpl::long_<2> const&) const
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
      table<value_t, nt2::of_size_<2, 2> >  g;
      size_t n = size(r, 2);
      size_t m = size(r, 1);
      if (orient == 'c')
      {
        //   remove the j-th column.  n = number of columns in modified r.
        r1 = nt2::cath(r(nt2::_, nt2::_(1, j-1)), r(nt2::_,nt2::_(j+1, nt2::end_)));
        q1 = q;
        --n;
        //  r now has nonzeros below the diagonal in columns j through n.
        //     r = [x | x x x         [x x x x
        //          0 | x x x          0 * * x
        //          0 | + x x    g     0 0 * *
        //          0 | 0 + x   --->   0 0 0 *
        //          0 | 0 0 +          0 0 0 0
        //          0 | 0 0 0]         0 0 0 0]
        //  use givens rotations to zero the +'s, one at a time, from left to right.

        for(size_t k = j; k <= nt2::min(n,m-1); ++k)
        {
          BOOST_AUTO_TPL(p, nt2::cons(k, k+1));
          tie(g,r1(p, k)) = nt2::planerot(r1(p,k));
          if (k < n)
          {
            r1(p,nt2::_(k+1, n)) = nt2::mtimes(g,r1(p,nt2::_(k+1, n)));
          }
          q1(nt2::_,p) = nt2::mtimes(q1(nt2::_,p), nt2::ct(g));
         }
        // if q is not square, q is from economy size qr(a,0).
        // both q and r need further adjustments.
        size_t mq = size(q, 1);
        size_t nq = size(q, 2);
        if (mq != nq)
        {
          r1(m,nt2::_)=_();
          q1(nt2::_,nq)=_();
        }
      }
      else
      {
        r1 = r;
        // this permutes row 1 of q*r to row j of q(p,:)*r
        if (j != 1)
        {
          BOOST_AUTO_TPL(p, nt2::cath(nt2::cath(j, nt2::_(size_t(1), j-1)), nt2::_(j+1, m)));
          q1 = q(p,nt2::_);
        }
        table<value_t, _1D> fqrt = nt2::colvect(q1(1,nt2::_));
        //  fqrt is the transpose of the first row of q.
        //  fqrt = [x         [1
        //          -          -
        //          +    g     0
        //          +   --->   0
        //          +          0
        //          +          0
        //          +]         0]
        //
        //  use givens rotations to zero the +'s, one at a time, from bottom to top.
        //  the result will have a "1" in the first entry.
        //
        //  apply the same rotations to r, which becomes upper hessenberg.
        //     r = [x x x x          [* * * *
        //          -------           -------
        //            x x x     g     * * * *
        //              x x    --->     * * *
        //                x               * *
        //          0 0 0 0                 *
        //          0 0 0 0]          0 0 0 0]
        //
        //  under (the transpose of) the same rotations, q becomes
        //     q = [x | x x x x x         [1 | 0 0 0 0 0
        //          --|----------          --|----------
        //          x | x x x x x    g'    0 | * * * * *
        //          x | x x x x x   --->   0 | * * * * *
        //          x | x x x x x          0 | * * * * *
        //          x | x x x x x          0 | * * * * *
        //          x | x x x x x]         0 | * * * * *]

        for(size_t i = m; i >= 2; --i)
        {
          BOOST_AUTO_TPL(p, nt2::cons(i-1, i));
          nt2::tie(g, fqrt(p)) = nt2::planerot(fqrt(p));
          //       tab_t rr = r1(p,nt2::_(i-1, n));
          r1(p,nt2::_(i-1, n)) = nt2::mtimes(g, r1(p,nt2::_(i-1, n)));
         //      tab_t qq = q1(nt2::_,p);
          q1(nt2::_,p) = nt2::mtimes(q1(nt2::_,p), nt2::ct(g));
        }
        //  the boxed off (---) parts of q and r are the desired factors.
        tab_t qq = q1(nt2::_(2, nt2::end_),_(2, nt2::end_));
        q1 = qq;
        tab_t rr = r1(_(2, nt2::end_),nt2::_);
        r1 = rr;
       }
     }

  };
} }

#endif
