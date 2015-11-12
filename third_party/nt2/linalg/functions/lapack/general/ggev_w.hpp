//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGEV_W_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGEV_W_HPP_INCLUDED

#include <nt2/linalg/functions/ggev_w.hpp>
#include <nt2/linalg/details/lapack/declare/ggev.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/functions/details/combine.hpp>

namespace nt2 { namespace ext
{
//---------------------------------------------Real-double------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))             //beta
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(dggev) ( &jobvl, &jobvr
                         , &n
                         , 0, &lda
                         , 0, &ldb
                         , 0 /*alphar*/, 0 /*alphai*/
                         , 0 /*beta*/
                         , 0, &ldvl
                         , 0, &ldvr
                         , wk.main(), details::query()
                         , &info);
      info = nt2::ggev_w(a, b, alpha, beta, wk);
      return info;
    }
  };

  //---------------------------------------------Real-float------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))             //beta
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(sggev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0 /*b*/, &ldb
                         , 0/*alphar*/, 0/*alphai*/
                         , 0/*beta*/
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), details::query()
                         , &info);
      info = nt2::ggev_w(a, b, alpha, beta, wk);
      return info;
    }
  };

  //---------------------------------------------complex-double------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))  //beta
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(zggev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0 /*b*/, &ldb
                         , 0/*alpha*/
                         , 0/*beta*/
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), details::query()
                         , wk.reals()
                         , &info);
      info = nt2::ggev_w(a, b, alpha, beta, wk);
      return info;
    }
  };

  //---------------------------------------------complex-float------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))  //beta
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(cggev) ( &jobvl, &jobvr
                         , &n
                         , 0 /*a*/, &lda
                         , 0 /*b*/, &ldb
                         , 0/*alpha*/
                         , 0/*beta*/
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), details::query()
                         , wk.reals()
                         , &info);
      info = nt2::ggev_w(a, b, alpha, beta, wk);
      return info;
    }
  };

  ////////////////////////////////////////////////////workspace is ready//////////////////////////////////
  //---------------------------------------------Real-double------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))             //beta
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, WK& wk) const
    {
      typedef typename A0::value_type type_t;
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2::container::table<type_t> alphar(of_size(n, 1)), alphai(of_size(n, 1));
      beta.resize(of_size(n, 1));
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      NT2_F77NAME(dggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alphar.raw(), alphai.raw()
                         , beta.raw()
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), &wn
                         , &info);
      combine_eigens(alphar, alphai, alpha);
      return info;
    }
  };


  //---------------------------------------------Real-float------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))             //beta
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, WK& wk) const
    {
      typedef typename A0::value_type type_t;
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2::container::table<type_t> alphar(of_size(n, 1)), alphai(of_size(n, 1));
      beta.resize(of_size(n, 1));
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      NT2_F77NAME(sggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alphar.raw(), alphai.raw()
                         , beta.raw()
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), &wn
                         , &info);
      combine_eigens(alphar, alphai, alpha);
      return info;
    }
  };

  //---------------------------------------------complex-double------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))  //beta
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, WK& wk) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      wk.resize_reals(8*n);
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(zggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alpha.raw()
                         , beta.raw()
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), &wn
                         , wk.reals()
                         , &info);
      return info;
    }
  };

  //---------------------------------------------complex-float------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))  //beta
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, WK& wk) const
    {
      result_type info = 0;
      char jobvr = 'N';
      char jobvl = 'N';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      wk.resize_reals(8*n);
      nt2_la_int ldvl = 1;
      nt2_la_int ldvr = 1;
      NT2_F77NAME(cggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alpha.raw()
                         , beta.raw()
                         , 0/*vl*/, &ldvl
                         , 0/*vr*/, &ldvr
                         , wk.main(), &wn
                         , wk.reals()
                         , &info);
      return info;
    }
  };
} }

#endif
