//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEESX1_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEESX1_HPP_INCLUDED

#include <nt2/linalg/functions/geesx1.hpp>
#include <nt2/linalg/details/lapack/declare/geesx.hpp>
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

//---------------------------------------------Real-double-no w no u------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              (scalar_<double_<A1> > )
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      nt2_la_int sdim_ = 0;
       result_type info = 0;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = 1;
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
      wk.prepare_main();
      wk.resize_main(nt2::sqr(n+1));
      wk.resize_reals(n);
      wk.resize_logicals(1);
      info = nt2::geesx(a, A1(1), wk);
      return info;
     }
  };

   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              (scalar_<single_<A1> > )
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      result_type info;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = 1;
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
      wk.prepare_main();
      wk.resize_main(nt2::sqr(n+1));
      wk.resize_reals(n);
      wk.resize_logicals(1);
      info = nt2::geesx(a, A1(1), wk);
      return info;

    }
  };
  /// INTERNAL ONLY - workspace ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              (scalar_<single_<A1> > )
                              (unspecified_<WK>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1 , WK& wk) const
    {
      result_type info = 0;
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      nt2_la_int n = nt2::width(a);
      nt2_la_int sdim_ = 0;
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldu = 1;
      nt2::container::table<float> wr(of_size(n, 1)), wi(of_size(n, 1));
      nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
      nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
      nt2_la_int wint = wk.integers_need();
      NT2_F77NAME(sgeesx) ( &jobu, &sort
                          , nt2::details::selectall2, &sense
                          , &n, a.raw()
                          , &lda, &sdim_
                          , wr.raw(),  wi.raw()
                          , 0, &ldu
                          , 0, 0
                          , wk.main(), &wn
                          , wk.integers(), &wint
                          , wk.logicals(), &info
                          );
      return info;
    }
  };
  /// INTERNAL ONLY - workspace ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              (scalar_<double_<A1> > )
                              (unspecified_<WK>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1 , WK& wk) const
    {
      result_type info = 0;
       char sort =  'N';
       char sense = 'N';
       char jobu  = 'N';
       nt2_la_int sdim_ = 0;
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = nt2::max(a.leading_size(), One<size_t>());
       nt2_la_int ldu = 1;
       nt2::container::table<double> wr(of_size(n, 1)), wi(of_size(n, 1));
       nt2_la_int ebs = details::EnvBlockSize(9, "NAME", " ", 0, 0, 0, 0);
       nt2_la_int wn =  nt2::max(ebs, n)*(n+1);
       nt2_la_int wint = wk.integers_need();
       NT2_F77NAME(dgeesx) ( &jobu, &sort
                           , nt2::details::selectall2, &sense
                           , &n, a.raw()
                           , &lda, &sdim_
                           , wr.raw(), wi.raw()
                           , 0, &ldu
                           , 0, 0
                           , wk.main(), &wn
                           , wk.integers(), &wint
                           , wk.logicals(), &info);
       return info;
    }
  };

//---------------------------------------------Complex-double no w no u------------------------------------------------//


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              (scalar_<complex_ < double_<A1> > > )
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      result_type info;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu = 1;
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
      wk.resize_reals(nt2::sqr(n+1));
      wk.resize_logicals(1);
      wk.resize_main(nt2::sqr(n+1));
      info = nt2::geesx(a, A1(0), wk);
      return info;
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              (scalar_<complex_ < double_<A1> > > )
                              (unspecified_<WK>)                                             //workspace
                            )
 {
     typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1, WK& wk) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu =  1;
      nt2_la_int sdim_ = 0;
      nt2_la_int wn =  nt2::sqr(n+1);
      nt2::container::table<typename A0::value_type> w(of_size(n, 1));
      NT2_F77NAME(zgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, a.raw()
                          , &lda, &sdim_
                          , w.raw(), 0
                          , &ldu, 0
                          , 0, wk.main()
                          , &wn, wk.reals()
                          , wk.logicals(), &info
                          );
      return info;
     }
  };

//---------------------------------------------Complex-float no w no u------------------------------------------------//


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              (scalar_<complex_ < single_<A1> > > )
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      result_type info;
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu = 1;
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
      wk.resize_reals(nt2::sqr(n+1));
      wk.resize_logicals(1);
      wk.resize_main(nt2::sqr(n+1));
      info = nt2::geesx(a, A1(0), wk);
      return info;
    }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::geesx1_, tag::cpu_
                            , (A0)(S0)(A1)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              (scalar_<complex_ < single_<A1> > > )
                              (unspecified_<WK>)                                             //workspace
                            )
 {
     typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1, WK& wk) const
    {
      char sort =  'N';
      char sense = 'N';
      char jobu  = 'N';
      result_type info;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(n == nt2_la_int(nt2::width(a)), "input must be square");
      nt2_la_int lda = a.leading_size();
      nt2_la_int ldu =  1;
      nt2_la_int sdim_ = 0;
      nt2_la_int wn =  nt2::sqr(n+1);
      nt2::container::table<typename A0::value_type> w(of_size(n, 1));
      NT2_F77NAME(cgeesx) ( &jobu, &sort
                          , nt2::details::selectall, &sense
                          , &n, a.raw()
                          , &lda, &sdim_
                          , w.raw(), 0
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
