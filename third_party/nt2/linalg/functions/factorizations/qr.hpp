//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_QR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_QR_HPP_INCLUDED

#include <nt2/include/functions/qr.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/geqp3.hpp>
#include <nt2/include/functions/geqrf.hpp>
#include <nt2/include/functions/gqr.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/mqr.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/linalg/options.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //QR Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qr_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qr_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };



  //============================================================================
  //[Q,R] = QR(A)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qr_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::qr_
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
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type     child0;
    typedef typename child0::value_type                                      type_t;
    typedef typename meta::as_real<type_t>::type                            rtype_t;
    typedef typename meta::as_integer<rtype_t>::type                        itype_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>        o_semantic;
    typedef nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D>    i_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

  private:
    /// INTERNAL ONLY - x = qr(a)
    /// return a matrix x such that triu(x) is the upper triangular factor r.
    /// this is the direct return of LAPACK ?geqp3, however tau is lost (and so q)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // 1 input
              , boost::mpl::long_<1> const& // 1 output
              ) const
    {
      eval1_1(a0, a1, nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY - x = qr(a, econ_/0)
    /// return a matrix x such that triu(x) is the upper triangular factor r.
    /// this is the direct return of LAPACK ?geqp3, however tau is lost (and so q)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // 2 input
              , boost::mpl::long_<1> const& // 1 output
              ) const
    {
      eval2_1(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    /// INTERNAL ONLY - [q, r] = qr(a)
    /// where a is m-by-n, produces an m-by-n upper triangular matrix r
    ///  and an m-by-m unitary matrix q so that a = q*r.
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&  // 1 input
              , boost::mpl::long_<2> const&  // 2 output
              ) const
    {
      eval2_2(a0, a1, nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY - [q, r, e] = qr(a)
    /// produces unitary q, upper triangular r and a
    /// permutation row vector e so that a(e, _)= q*r.
    /// the column permutation e is chosen so that abs(diag_of(r)) is decreasing.
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&  // 1 input
              , boost::mpl::long_<3> const&  // 3 output
              ) const
    {
      eval2_3(a0, a1, nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY - [x, y] = qr(a, raw_/matrix_/vector_/econ_/0 )
    /// with raw_
    ///  [x, tau] = qr(a, raw_)
    /// returns a matrix x such that triu(x) is the upper triangular factor r.
    /// The elements below the diagonal, together with the array tau, represent the
    /// unitary matrix Q as a product of min(M,N) elementary reflectors.
    /// tau contains The scalar factors of the elementary reflectors.
    /// This is the direct return of LAPACK ?geqp3
    ///
    /// with matrix_/vector is the same as  [q, r] = qr(a)
    /// [q, r] = qr(a, econ_) or  [q, r] = qr(a, 0)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      //1_2 means  1 input 2 outputs
      eval2_2(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    /// INTERNAL ONLY - [q, r, e] = qr(a, vector_/matrix_)
    /// with vector_
    /// produces unitary q, upper triangular r and a
    /// permutation row vector e so that a(e, _)= q*r.
    /// the column permutation e is chosen so that abs(diag_of(r)) is decreasing.
    /// with matrix_
    /// produces unitary q, upper triangular r and a
    /// permutation matrix e so that a*e = q*r.
    /// the column permutation e is chosen so that abs(diag_of(r)) is decreasing.
    /// Same as   [q, r, e] = qr(a)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // 2 input
              , boost::mpl::long_<3> const& // 2 output
              ) const
    {
      eval2_3(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }


    ///////////////////////////////////////////////////////////////////////////////
    // evali_j bunch
    ///////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 1i 1o: x  = qr(a)
    BOOST_FORCEINLINE
    void eval1_1 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, r
                           , boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      o_semantic tau(of_size(height(r), 1));
      NT2_LAPACK_VERIFY(nt2::geqrf( boost::proto::value(r)
                                  , tau));
      assign_swap(boost::proto::child_c<0>(a1), r);
    }

    /// INTERNAL ONLY: 2i 1o raw_: x  = qr(a, raw_)
    BOOST_FORCEINLINE
    void eval2_1 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      eval1_1(a0, a1, nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY: 2i 1o upper_: x  = qr(a, upper_)
    BOOST_FORCEINLINE
    void eval2_1 ( A0& a0, A1& a1
                   , const nt2::policy<ext::upper_>&
                   ) const
    {
       nt2::container::table<type_t> work;
       NT2_AS_TERMINAL_INOUT(o_semantic
                            , r, boost::proto::child_c<0>(a0), work);
       o_semantic tau(of_size(height(r), 1));
       NT2_LAPACK_VERIFY(nt2::geqrf( boost::proto::value(r)
                                   ,tau));
       boost::proto::child_c<0>(a1) = triu(r);
    }

    /// INTERNAL ONLY: 2i 1o econ_: x  = qr(a, econ_)
    BOOST_FORCEINLINE
    void eval2_1 ( A0& a0, A1& a1
                   , const nt2::policy<ext::econ_>&
                   ) const
    {
      eval1_1(a0, a1, nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY: 2i 1o 0: x  = qr(a, 0)
    BOOST_FORCEINLINE
    void eval2_1 ( A0& a0, A1& a1
                   , const int&
                   ) const
    {
      eval1_1(a0, a1, nt2::policy<ext::raw_>());
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 2o raw_: tie(x, tau) = qr(a, raw_)
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, x
                           , boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, tau
                         , boost::proto::child_c<1>(a1));
      tau.resize(of_size(dim(x), 1));
      NT2_LAPACK_VERIFY(nt2::geqrf( boost::proto::value(x)
                                  , boost::proto::value(tau)));
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), tau);
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o raw_: tie(x, tau, ip) = qr(a, nt2::raw_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, x
                           , boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(o_semantic, tau
                         , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(i_semantic,  ip
                         , boost::proto::child_c<2>(a1));
      tau.resize(of_size(dim(x), 1));
      ip = nt2::zeros(nt2::width(x),1,nt2::meta::as_<nt2_la_int>());
      NT2_LAPACK_VERIFY(nt2::geqp3( boost::proto::value(x)
                                  , boost::proto::value(ip)
                                  , boost::proto::value(tau)));
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), tau);
      assign_swap(boost::proto::child_c<2>(a1), ip);
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 2o matrix_/econ_: tie(q, r) = qr(a, matrix_) or
    /// tie(q, r) = qr(a, econ_), only extracting phases differ
    template < class T >
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , const T&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , r, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic
                           , x, boost::proto::child_c<0>(a1));
      nt2::container::table<type_t>     tau;
      tie(x, tau) = qr(r, nt2::raw_);
      extract_qr(x, tau, r, T()); // extract raw or econ
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), r);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 2o vector_: tie(q, r) = qr(a, vector_)
    /// this is identical to  tie(q, r) = qr(a, matrix_)  ot  tie(q, r) = qr(a)
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , const nt2::policy<ext::vector_>&
                   ) const
    {
      eval2_2(a0, a1,  nt2::policy<ext::matrix_>()); //with 2 outputs vector_ is useless
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 2o vector_: tie(q, r) = qr(a, 0)
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                   , const int &
                   ) const
    {
      eval2_2(a0, a1, nt2::policy<ext::econ_>()); // 0 and econ_ are equivalent
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o vector_: tie(q, r, ip) = qr(a, econ_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::econ_>&
                   ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, r
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, x
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (i_semantic, ip
                           , boost::proto::child_c<2>(a1));
      nt2::container::table<type_t> tau;
      tie(x, tau, ip) = qr(r, nt2::raw_);

      extract_qr(x, tau, r, nt2::policy<ext::econ_>());
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), r);
      assign_swap(boost::proto::child_c<2>(a1), ip);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o vector_: tie(q, r, ip) = qr(a, 0)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const int &
                   ) const
    {
      eval2_3(a0, a1,  nt2::policy<ext::econ_>()); // 0 and econ_ are equivalent
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o vector_: tie(q, r, ip) = qr(a, vector_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::vector_>&
                   ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, r
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, x
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (i_semantic, ip
                           , boost::proto::child_c<2>(a1));
      nt2::container::table<type_t>     tau;
      tie(x, tau, ip) = qr(r, nt2::raw_);

      extract_qr(x, tau, r, nt2::policy<ext::raw_>());
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), r);
      assign_swap(boost::proto::child_c<2>(a1), ip);
    }

     ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o matrix_: tie(q, r, p) = qr(a, matrix_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::matrix_>&
                   ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, r
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, x
                           , boost::proto::child_c<0>(a1));
      nt2::container::table<type_t>     tau;
      nt2::container::table<nt2_la_int>  ip;
      tie(x, tau, ip) = qr(r, nt2::raw_);

      extract_qr(x, tau, r, nt2::policy<ext::raw_>());
      assign_swap(boost::proto::child_c<0>(a1), x);
      assign_swap(boost::proto::child_c<1>(a1), r);
      boost::proto::child_c<2>(a1) = eye(numel(ip), nt2::meta::as_<type_t>())(nt2::_, ip);
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    /// extraction helpers
    //////////////////////////////////////////////////////////////////////////////////////////

    /// INTERNAL ONLY - Helper for Q/R extraction
    template<typename XQ, typename TAU,typename R, typename CHOICE >
    BOOST_FORCEINLINE
    void extract_qr(XQ& xq, TAU& tau, R& r, CHOICE const &) const
    {
      nt2_la_int  m  = nt2::height(xq);
      nt2_la_int  n  = nt2::width(xq);
      typedef typename XQ::value_type xqtype_t;
      r = nt2::triu(xq);

      if (m>n)
      {
        nt2::container::table<xqtype_t> complete_q = nt2::eye(m,m, nt2::meta::as_<xqtype_t>());
        nt2::mqr( boost::proto::value(xq)
                , boost::proto::value(tau)
                , boost::proto::value(complete_q) );
        xq = complete_q;
      }
      else
      {
        if(m < n)
        {
          /// TODO: Remove when aliasing works
          nt2::container::table<xqtype_t> local(xq);
          xq = nt2::expand(local,nt2::of_size(m,m));
        }
        nt2::gqr( boost::proto::value(xq)
                , boost::proto::value(tau));
      }
    }


    /// INTERNAL ONLY - Helper for Q/R extraction economy mode
    template<typename XQ, typename TAU,typename R >
    BOOST_FORCEINLINE
    void extract_qr(XQ& xq, TAU& tau, R& r, nt2::policy<ext::econ_> const &) const
    {
      nt2_la_int  m  = nt2::height(xq);
      nt2_la_int  n  = nt2::width(xq);
      typedef typename XQ::value_type xqtype_t;

      // economy mode
      r = nt2::triu(xq(_(1,nt2::min(n, m)), _) );

      if(m < n)
      {
        /// TODO: Remove when aliasing works
        nt2::container::table<xqtype_t> local(xq);
        xq = nt2::expand(local,nt2::of_size(m,m));
      }

      nt2::gqr( boost::proto::value(xq)
              , boost::proto::value(tau));
    }

    ////////////////////////////////////////////////////////////////////////////
    // some utilitaries
    ////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY - Size of L/U
    template<typename W>
    BOOST_FORCEINLINE std::size_t dim(W const& work) const
    {
      return std::min(nt2::height(work),nt2::width(work));
    }
  };
} }

#endif
