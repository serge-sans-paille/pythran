//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_NSEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_NSEIG_HPP_INCLUDED

#include <nt2/linalg/functions/nseig.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/balance.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/gebak.hpp>
#include <nt2/include/functions/gebal.hpp>
#include <nt2/include/functions/geev_w.hpp>
#include <nt2/include/functions/geev_wvr.hpp>
#include <nt2/include/functions/geev_wvrvl.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nseig_, tag::cpu_
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

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nseig_, tag::cpu_
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

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nseig_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      return a0;
    }
  };

  //============================================================================
  //Eig computations
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nseig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::nseig_
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
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type    child0;
    typedef typename child0::value_type                                     type_t;
    typedef typename nt2::meta::as_real<type_t>::type                      rtype_t;
    typedef typename nt2::meta::as_complex<rtype_t>::type                  ctype_t;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::_2D> desired_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - W = NSEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_2(a0, a1, nt2::policy<ext::vector_>());
    }

    /// INTERNAL ONLY - W = NSEIG(A, matrix_/vector_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    /// INTERNAL ONLY: 1o 2i
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic, a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, w, boost::proto::child_c<0>(a1));
      w.resize(of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::geev_w( boost::proto::value(a)
                                   , boost::proto::value(w)));
      boost::proto::child_c<0>(a1) = w;
    }

    /// INTERNAL ONLY: 1o 2i
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic, a, boost::proto::child_c<0>(a0), work);
      nt2::container::table <ctype_t, _2D > w(of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::geev_w( boost::proto::value(a)
                                  , boost::proto::value(w)
                                  ));
      boost::proto::child_c<0>(a1) = from_diag(w); //from_diag doesnt support aliasing currently
    }

    //==========================================================================
    /// INTERNAL ONLY - [VR, W]= NSEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2(a0, a1,nt2::policy<ext::matrix_>());
    }


    //==========================================================================
    /// INTERNAL ONLY - [VR, W]= NSEIG(A,  matrix_/vector_/balance_/no_balance_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

   /// INTERNAL ONLY: 2o 2i
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      size_t n = height(a);
      w.resize(of_size(n, 1));
      vr.resize(of_size(n, n));
      NT2_LAPACK_VERIFY(nt2::geev_wvr( boost::proto::value(a)
                                     , boost::proto::value(w)
                                     , boost::proto::value(vr)
                                     ));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = vr;
    }

    /// INTERNAL ONLY: 2o 2i
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      size_t n = height(a);
      nt2::container::table<ctype_t> w(of_size(n, 1));
      vr.resize(of_size(n, n));
      NT2_LAPACK_VERIFY(nt2::geev_wvr( boost::proto::value(a)
                                     , boost::proto::value(w)
                                     , boost::proto::value(vr)
                                     ));
      boost::proto::child_c<1>(a1) = from_diag(w);
      boost::proto::child_c<0>(a1) = vr;
    }

    /// INTERNAL ONLY: 2o 2i
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::balance_> const &
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::balance_>());
    }

    /// INTERNAL ONLY: 2o 2i
    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::no_balance_> const &
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::no_balance_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [VR, W, VL]= NSEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_3( a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::no_balance_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [VR, W, VL]= NSEIG(A, vector_/matrix_/balance_/no_balance_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_2(a0, a1, boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    /// INTERNAL ONLY: 3o 2i
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic, vl, boost::proto::child_c<2>(a1));
      size_t n = height(a);
      nt2::container::table<ctype_t> w(of_size(n, 1));
      vr.resize(of_size(n, n));
      vl.resize(of_size(n, n));
      NT2_LAPACK_VERIFY(nt2::geev_wvrvl( boost::proto::value(a)
                                       , boost::proto::value(w)
                                       , boost::proto::value(vr)
                                       , boost::proto::value(vl)
                                       ));
      boost::proto::child_c<1>(a1) = from_diag(w);
      boost::proto::child_c<0>(a1) = vr;
      boost::proto::child_c<2>(a1) = vl;
    }

    /// INTERNAL ONLY: 3o 2i
    BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic, vl, boost::proto::child_c<2>(a1));
      size_t n = height(a);
      vr.resize(of_size(n, n));
      vl.resize(of_size(n, n));
      w.resize(of_size(n, 1));
      NT2_LAPACK_VERIFY(nt2::geev_wvrvl( boost::proto::value(a)
                                       , boost::proto::value(w)
                                       , boost::proto::value(vr)
                                       , boost::proto::value(vl)
                                       ));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = vr;
      boost::proto::child_c<2>(a1) = vl;
    }

    /// INTERNAL ONLY: 3o 2i
    template < class T> BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::no_balance_> const &
                 ) const
    {
      eval3_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::no_balance_>());
    }

    /// INTERNAL ONLY: 3o 2i
    template < class T> BOOST_FORCEINLINE
    void eval3_2 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      eval3_3(a0, a1, nt2::policy<ext::matrix_>(), nt2::policy<ext::balance_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [W]= NSEIG(A, matrix_/vector_, balance_/no_balance_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0))
             , boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 1o 3i
    template < class T >
    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , T const &
                 ,  nt2::policy<ext::no_balance_> const &
                 ) const
    {
      eval1_2(a0, a1, T());
    }

    /// INTERNAL ONLY: 1o 3i
    template < class T >
    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::vector_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = balance(a);
      boost::proto::child_c<0>(a1) = nseig(b, nt2::policy<ext::vector_>());
    }
    /// INTERNAL ONLY: 1o 3i
    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::matrix_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> a = boost::proto::child_c<0>(a0);
      nt2::container::table<type_t> b = balance(a);
      boost::proto::child_c<0>(a1) = nseig(b); //as_temporary(b));

    }
    //==========================================================================
    /// INTERNAL ONLY - [V, W]= NSEIG(A, matrix_/vector_, balance_/no_balance_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0))
             , boost::proto::value(boost::proto::child_c<2>(a0)));
    }

    /// INTERNAL ONLY: 2o 3i
    template < class T> BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 ,  T  const &
                 ,  nt2::policy<ext::no_balance_> const &
                 ) const
    {
      eval2_2 (a0, a1, T());
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::vector_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic,  v, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));

      nt2_la_int ilo, ihi;
      nt2_la_int n = height(a);
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      NT2_LAPACK_VERIFY(gebal(boost::proto::value(a)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B'));
      tie(v, w) = nseig(a, nt2::policy<ext::vector_>());
      NT2_LAPACK_VERIFY(gebak( boost::proto::value(v)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B', 'R'));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = v;
    }

    /// INTERNAL ONLY: 2o 3i
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::matrix_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic,  v, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(a);
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      NT2_LAPACK_VERIFY(gebal( boost::proto::value(a)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B'));
      tie(v, w) = nseig(a, nt2::policy<ext::matrix_>());
      NT2_LAPACK_VERIFY(gebak( boost::proto::value(v)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B', 'R'));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = v;
    }


    //==========================================================================
    /// INTERNAL ONLY - [VR, W, VL]= NSEIG(A, matrix_/vector_, balance_/no_balance_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<3> const&
              ) const
    {
      eval3_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0))
             , boost::proto::value(boost::proto::child_c<2>(a0)));
    }

     /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3( A0& a0, A1& a1
                 ,  nt2::policy<ext::vector_>  const &
                 ,  nt2::policy<ext::no_balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      tie( boost::proto::child_c<0>(a1)
         , boost::proto::child_c<1>(a1)
         , boost::proto::child_c<2>(a1)) = nseig(a, nt2::policy<ext::vector_>());
    }

     /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3( A0& a0, A1& a1
                 ,  nt2::policy<ext::matrix_>  const &
                 ,  nt2::policy<ext::no_balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic, vl, boost::proto::child_c<2>(a1));
      nt2_la_int n = height(a);
      nt2::container::table<ctype_t> w(of_size(n, 1));
      tie( vr, w, vl) = nseig(a, nt2::policy<ext::vector_>());
      boost::proto::child_c<1>(a1) =  from_diag(w);
      boost::proto::child_c<0>(a1) = vr;
      boost::proto::child_c<2>(a1) = vl;
    }

    /// INTERNAL ONLY: 3o 3i
    BOOST_FORCEINLINE
    void eval3_3( A0& a0, A1& a1
                 ,  nt2::policy<ext::vector_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic, vl, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(a);
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      NT2_LAPACK_VERIFY(gebal(boost::proto::value(a)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B'));
      tie(vr, w, vl) = nseig(a, nt2::policy<ext::vector_>(), nt2::policy<ext::no_balance_>());
      NT2_LAPACK_VERIFY(gebak(boost::proto::value(vr),
                              boost::proto::value(scale)
                             , ilo, ihi, 'B', 'R'));
      NT2_LAPACK_VERIFY(gebak(boost::proto::value(vl)
                             , boost::proto::value(scale)
                             , ilo, ihi, 'B', 'L'));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = vr;
      boost::proto::child_c<2>(a1) = vl;
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void eval3_3 ( A0& a0, A1& a1
                 ,  nt2::policy<ext::matrix_>  const &
                 ,  nt2::policy<ext::balance_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(desired_semantic,  a, boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (desired_semantic, vr, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic, vl, boost::proto::child_c<2>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      nt2_la_int ilo, ihi;
      nt2_la_int n = height(a);
      nt2::container::table<rtype_t> scale(of_size(n, 1));
      NT2_LAPACK_VERIFY(gebal(boost::proto::value(a), boost::proto::value(scale), ilo, ihi, 'B'));
      tie(vr, w, vl) = nseig(a, nt2::policy<ext::matrix_>(), nt2::policy<ext::no_balance_>());
      NT2_LAPACK_VERIFY(gebak(boost::proto::value(vr),
                              boost::proto::value(scale), ilo, ihi, 'B', 'R'));
      NT2_LAPACK_VERIFY(gebak(boost::proto::value(vl),
                              boost::proto::value(scale), ilo, ihi, 'B', 'L'));
      boost::proto::child_c<1>(a1) = w;
      boost::proto::child_c<0>(a1) = vr;
      boost::proto::child_c<2>(a1) = vl;
    }

  };
} }

#endif


