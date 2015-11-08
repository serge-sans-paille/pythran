//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED

#include <nt2/linalg/functions/svd.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/gesvd_w.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::abs(a0);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
       return nt2::abs(a0);
    }
  };

  //============================================================================
  //SVD
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::svd_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::svd_
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
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>       r_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - S = SVD(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_2(a0, a1, nt2::policy<ext::raw_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - S = SVD(A, vector_/matrix_/raw_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_2(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));
    }


    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (r_semantic
                           , s, boost::proto::child_c<0>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      s.resize(nt2::of_size(std::min(m,n),1));

      NT2_LAPACK_VERIFY(nt2::gesvd_w( boost::proto::value(a)
                                    , boost::proto::value(s)
                                    ));
      assign_swap(boost::proto::child_c<0>(a1), s);
    }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2::container::table<rtype_t> s(nt2::of_size(std::min(m,n),1));

      NT2_LAPACK_VERIFY(nt2::gesvd_w( boost::proto::value(a)
                                    , boost::proto::value(s)
                                    ));
      boost::proto::child_c<0>(a1) = nt2::expand(nt2::from_diag(s),height(a),width(a));
    }

    //==========================================================================
    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_>
                 ) const
    {
      eval1_2(a0, a1
             , nt2::policy<ext::raw_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X, matrix_/vector_/raw_/0)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval2_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));

    }
    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X, matrix_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u
                           , boost::proto::child_c<0>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      u.resize(nt2::of_size(m,m));
      nt2::container::table<type_t> vt(of_size(n, n));
      nt2::container::table<rtype_t>  s(of_size(min(n, m), 1));
      NT2_LAPACK_VERIFY(nt2::gesvd( boost::proto::value(a)
                                  , boost::proto::value(s)
                                  , boost::proto::value(u)
                                  , boost::proto::value(vt)
                                  , 'A', 'A'));
      assign_swap(boost::proto::child_c<0>(a1), u);
      boost::proto::child_c<2>(a1) = nt2::ctrans(vt);
      boost::proto::child_c<1>(a1) = nt2::expand(nt2::from_diag(s),height(a),width(a));
    }

    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X, vector_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, s
                           , boost::proto::child_c<1>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      s.resize(nt2::of_size(std::min(m,n),1));
      u.resize(nt2::of_size(m,m));
      nt2::container::table<type_t> vt(of_size(n, n));
      NT2_LAPACK_VERIFY(nt2::gesvd( boost::proto::value(a)
                                  , boost::proto::value(s)
                                  , boost::proto::value(u)
                                  , boost::proto::value(vt)
                                  , 'A', 'A'));
      assign_swap(boost::proto::child_c<0>(a1), u);
      boost::proto::child_c<2>(a1) = nt2::ctrans(vt);
      assign_swap(boost::proto::child_c<1>(a1), s);
    }


    //==========================================================================
    // bunch of evali_j
    //==========================================================================
    /// INTERNAL ONLY - [U,S,V] = SVD(X,0)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
              , int const&
              ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u
                           , boost::proto::child_c<0>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2_la_int  d  = std::min(n, m);
      nt2::container::table<type_t> vt(of_size(n, n));
      nt2::container::table<rtype_t>  s(of_size(d, 1));
      char jobu = (m>n) ? 'S' :'A';
      u.resize(nt2::of_size(m,d));
      NT2_LAPACK_VERIFY(nt2::gesvd( boost::proto::value(a)
                                  , boost::proto::value(s)
                                  , boost::proto::value(u)
                                  , boost::proto::value(vt)
                                  , jobu, 'A'));

      boost::proto::child_c<2>(a1) = nt2::ctrans(vt);
      boost::proto::child_c<1>(a1) =  nt2::expand(nt2::from_diag(s),width(u),height(vt));
      assign_swap(boost::proto::child_c<0>(a1), u);
    }


    /// INTERNAL ONLY - [U,S,V] = SVD(X,econ_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , const nt2::policy<ext::econ_>&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic
                           , u, boost::proto::child_c<0>(a1));
      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);
      nt2::container::table<rtype_t>  s(of_size(std::min(m,n), 1));
      nt2::container::table<type_t> vt;
      char jobu = 'A';
      char jobvt= 'A';
      if(m>=n)
      {
        jobu = 'S';
        u.resize(nt2::of_size(m,n));
        vt.resize(nt2::of_size(n,n));
      }
      else if (m<n)
      {
        jobvt = 'S';
        u.resize(nt2::of_size(m,m));
        vt.resize(nt2::of_size(m,n));
      }
      NT2_LAPACK_VERIFY(nt2::gesvd( boost::proto::value(a)
                                  , boost::proto::value(s)
                                  , boost::proto::value(u)
                                  , boost::proto::value(vt)
                                  , jobu, jobvt ));

      boost::proto::child_c<1>(a1) = nt2::from_diag(s);
      boost::proto::child_c<2>(a1) = nt2::ctrans(vt);
      assign_swap(boost::proto::child_c<0>(a1), u);
    }

    /// INTERNAL ONLY - [U,S,VT] = SVD(X,raw_)
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , const nt2::policy<ext::raw_>&
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (o_semantic, u
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (o_semantic, vt
                           , boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, s
                           , boost::proto::child_c<1>(a1));

      nt2_la_int  m  = nt2::height(a);
      nt2_la_int  n  = nt2::width(a);

      u.resize(nt2::of_size(m,m));
      vt.resize(of_size(n, n));
      s.resize(of_size(min(n, m), 1));

      NT2_LAPACK_VERIFY(nt2::gesvd( boost::proto::value(a)
                                  , boost::proto::value(s)
                                  , boost::proto::value(u)
                                  , boost::proto::value(vt)
                                  , 'A', 'A'));
      assign_swap(boost::proto::child_c<1>(a1), s);
      assign_swap(boost::proto::child_c<2>(a1), vt);
      assign_swap(boost::proto::child_c<0>(a1), u);
    }
  };
} }

#endif


