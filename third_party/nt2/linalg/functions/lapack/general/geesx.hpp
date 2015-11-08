//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEESX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEESX_HPP_INCLUDED

#include <nt2/linalg/functions/geesx.hpp>
#include <nt2/linalg/details/lapack/declare/geesx.hpp>
#include <nt2/linalg/functions/details/combine.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/envblocksize.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-double------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >))             //u
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'V';
      nt2_la_int sdim_ = 0;
      result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int liwork = -1;
      NT2_F77NAME(dgeesx) ( &jobu, &sort
                          , &nt2::details::selectall2, &sense
                          , &n, 0 /*a*/
                          , &lda, &sdim_
                          , 0/*wr*/, 0/*wi*/
                          , 0/*u*/, &ldu
                          , 0, 0
                          , wk.main(), details::query()
                          , wk.integers(), &liwork
                          , wk.logicals(), &info);
      nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
      nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
      wk.resize_main(wn);
      wk.resize_integers(1);
      wk.resize_logicals(1);
      info = nt2::geesx(a, w, u, wk);
      return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> > , S1 >)) //w
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >))             //u
                              (unspecified_<WK>)                                              //workspace
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u, WK& wk) const
     {
       result_type info;
       char sort =  'N';
       char sense = 'N';
       char jobu  = 'V';
       nt2_la_int sdim_ = 0;
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
       nt2_la_int ldu = nt2::max(u.leading_size(), One<size_t>());
       nt2::container::table<double> wr(of_size(n, 1)), wi(of_size(n, 1));
       nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
       nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
       nt2_la_int wint = wk.integers_need();
       NT2_F77NAME(dgeesx) ( &jobu, &sort
                           , nt2::details::selectall2, &sense
                           , &n, a.raw()
                           , &lda, &sdim_
                           , wr.raw(), wi.raw()
                           , u.raw(), &ldu
                           , 0, 0
                           , wk.main(), &wn
                           , wk.integers(), &wint
                           , wk.logicals(), &info);
       combine_eigens(wr, wi, w);
       return info;
     }
  };

//---------------------------------------------Real-single------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))              //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> > , S1 >))  //w
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >))              //u
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u) const
    {
      result_type info = 0;
      char sort =  'N';
      char sense = 'N';
      char jobu =  'V';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda   = a.leading_size();
      nt2_la_int ldu   = nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int sdim_ = 0;
      nt2_la_int liwork = -1;
      NT2_F77NAME(sgeesx) ( &jobu, &sort
                          , &nt2::details::selectall2, &sense
                          , &n, 0 /*a*/
                          , &lda, &sdim_
                          , 0/*wr*/, 0/*wi*/
                          , 0/*u*/, &ldu
                          , 0, 0
                          , wk.main(), details::query()
                          , wk.integers(), &liwork
                          , wk.logicals(), &info);
      nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
      nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
      wk.resize_main(wn);
      wk.resize_integers(1);
      wk.resize_logicals(1);
      info = nt2::geesx(a, w, u, wk);
      return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //w
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >))             //u
                              (unspecified_<WK>)                                              //workspace
                            )
  {
     typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u, WK& wk) const
     {
       result_type info = 0;
       char sort =  'N';
       char sense = 'N';
       char jobu  = 'V';
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = a.leading_size();
       nt2_la_int ldu = nt2::max(u.leading_size(), One<size_t>());
       nt2_la_int sdim_ = 0;
       nt2::container::table<float> wr(of_size(n, 1)), wi(of_size(n, 1));
       nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
       nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
       nt2_la_int wint = wk.integers_need();
       NT2_F77NAME(sgeesx) ( &jobu, &sort
                           , nt2::details::selectall2, &sense
                           , &n, a.raw()
                           , &lda, &sdim_
                           , wr.raw(), wi.raw()
                           , u.raw(), &ldu
                           , 0, 0
                           , wk.main(), &wn
                           , wk.integers(), &wint
                           , wk.logicals(), &info);

       combine_eigens(wr, wi, w);
       return info;
     }
  };




  //////////////////////////////////////// Complex /////////////////////////////////////////////////////////

//---------------------------------------------Complex-single------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >)) //w
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >)) //u
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'V';
      result_type info;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int sdim_ = 0;
      NT2_F77NAME(cgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, 0
                          , &lda, &sdim_
                          , 0, 0
                          , &ldu, 0
                          , 0, wk.main()
                          , details::query(), wk.reals()
                          , wk.logicals(), &info);
      wk.prepare_main();
      wk.resize_main(nt2::sqr(n+1));
      wk.resize_reals(n);
      wk.resize_logicals(n);
      info = nt2::geesx(a, w, u, wk);
      return info;
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >)) //ws
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >)) //u
                              (unspecified_<WK>)                                             //workspace
                            )
 {
     typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u, WK& wk) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'V';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int sdim_ = 0;
      nt2_la_int wn = nt2::sqr(n+1);
      NT2_F77NAME(cgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, a.raw()
                          , &lda, &sdim_
                          , w.raw(), u.raw()
                          , &ldu, 0
                          , 0, wk.main()
                          , &wn, wk.reals()
                          , wk.logicals(), &info
                          );
      return info;
    }
  };

//---------------------------------------------Complex-double------------------------------------------------//


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >)) //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >)) //u
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w
                                            , A2& u
                                            ) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'V';
      result_type info;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu =  nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int sdim_ = 0;
      NT2_F77NAME(zgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, 0
                          , &lda, &sdim_
                          , 0, 0
                          , &ldu, 0
                          , 0, wk.main()
                          , details::query(), wk.reals()
                          , wk.logicals(), &info);
      wk.prepare_main();
      wk.resize_reals(n);
      wk.resize_logicals(n);
      wk.resize_main(nt2::sqr(n+1));
      info = nt2::geesx(a, w, u, wk);
      return info;
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >)) //w
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >)) //u
                              (unspecified_<WK>)                                             //workspace
                            )
 {
     typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, A2& u, WK& wk) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'V';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu =  nt2::max(u.leading_size(), One<size_t>());
      nt2_la_int sdim_ = 0;
      w.resize(of_size(n, 1));
      u.resize(of_size(n, n));
      nt2_la_int wn =  nt2::sqr(n+1);
      NT2_F77NAME(zgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, a.raw()
                          , &lda, &sdim_
                          , w.raw(), u.raw()
                          , &ldu, 0
                          , 0, wk.main()
                          , &wn, wk.reals()
                          , wk.logicals(), &info
                          );
      return info;
     }
  };

} }

#endif
