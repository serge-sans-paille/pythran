//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGEV_WVRVL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GGEV_WVRVL_HPP_INCLUDED

#include <nt2/linalg/functions/ggev_wvr.hpp>
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
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))             //beta
                              ((container_<nt2::tag::table_,  complex_<double_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<double_<A5> >, S5 >))  //vl
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = n;
      nt2_la_int ldvr = n;
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
      info = nt2::ggev_wvrvl(a, b, alpha, beta, vr, vl, wk);
      return info;
    }
  };

  //---------------------------------------------Real-float------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))             //beta
                              ((container_<nt2::tag::table_,  complex_<single_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<single_<A5> >, S5 >))  //vl
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = n;
      nt2_la_int ldvr = n;
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
      info = nt2::ggev_wvrvl(a, b, alpha, beta, vr, vl, wk);
      return info;
    }
  };

  //---------------------------------------------complex-double------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))  //beta
                              ((container_<nt2::tag::table_,  complex_<double_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<double_<A5> >, S5 >))  //vl
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = n;
      nt2_la_int ldvr = n;
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
      info = nt2::ggev_wvrvl(a, b, alpha, beta, vr, vl, wk);
      return info;
    }
  };

  //---------------------------------------------complex-float------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))  //beta
                              ((container_<nt2::tag::table_,  complex_<single_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<single_<A5> >, S5 >))  //vl
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      details::workspace<typename A0::value_type> wk;
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = n;
      nt2_la_int ldvr = n;
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
      info = nt2::ggev_wvrvl(a, b, alpha, beta, vr, vl, wk);
      return info;
    }
  };

  ////////////////////////////////////////////////////workspace is ready//////////////////////////////////
  //---------------------------------------------Real-double------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >))             //beta
                              ((container_<nt2::tag::table_,  complex_<double_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<double_<A5> >, S5 >))  //vl
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl, WK& wk) const
    {
      typedef typename A0::value_type type_t;
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2::container::table<type_t> alphar(of_size(n, 1)), alphai(of_size(n, 1))
        , rvr(of_size(n, n)), rvl(of_size(n, n));
      beta.resize(of_size(n, 1));
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = rvl.leading_size();
      nt2_la_int ldvr = rvr.leading_size();
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      NT2_F77NAME(dggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alphar.raw(), alphai.raw()
                         , beta.raw()
                         , rvl.raw(), &ldvl
                         , rvr.raw(), &ldvr
                         , wk.main(), &wn
                         , &info);
      combine_eigens(alphar, alphai, alpha);
      combine_vects(rvr, alphai, vr);
      combine_vects(rvl, alphai, vl);
      return info;
    }
  };


  //---------------------------------------------Real-float------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >))             //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))             //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >))             //beta
                              ((container_<nt2::tag::table_,  complex_<single_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<single_<A5> >, S5 >))  //vl
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl, WK& wk) const
    {
      typedef typename A0::value_type type_t;
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2::container::table<type_t> alphar(of_size(n, 1)), alphai(of_size(n, 1))
        , rvr(of_size(n, n)), rvl(of_size(n, n));
      beta.resize(of_size(n, 1));
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int ldvl = rvl.leading_size();
      nt2_la_int ldvr = rvr.leading_size();
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      NT2_F77NAME(sggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alphar.raw(), alphai.raw()
                         , beta.raw()
                         , rvl.raw(), &ldvl
                         , rvr.raw(), &ldvr
                         , wk.main(), &wn
                         , &info);
      combine_eigens(alphar, alphai, alpha);
      combine_vects(rvr, alphai, vr);
      combine_vects(rvl, alphai, vl);
      return info;
    }
  };

  //---------------------------------------------complex-double------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<double_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >))  //beta
                              ((container_<nt2::tag::table_,  complex_<double_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<double_<A5> >, S5 >))  //vl
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl, WK& wk) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      wk.resize_reals(8*n);
      vr.resize(of_size(n, n));
      vl.resize(of_size(n, n));
      nt2_la_int ldvl = vl.leading_size();;
      nt2_la_int ldvr = vr.leading_size();
      NT2_F77NAME(zggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alpha.raw()
                         , beta.raw()
                         , vl.raw(), &ldvl
                         , vr.raw(), &ldvr
                         , wk.main(), &wn
                         , wk.reals()
                         , &info);
      return info;
    }
  };

  //---------------------------------------------complex-float------------------------------------------------//
  /// INTERNAL ONLY - workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ggev_wvrvl_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(S4)(A5)(S5)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))  //a
                              ((container_<nt2::tag::table_,  complex_<single_<A1> >, S1 >))  //b
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >))  //alpha
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >))  //beta
                              ((container_<nt2::tag::table_,  complex_<single_<A4> >, S4 >))  //vr
                              ((container_<nt2::tag::table_,  complex_<single_<A5> >, S5 >))  //vl
                              (unspecified_<WK>)                                              //workspace
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a, A1& b, A2& alpha, A3& beta, A4& vr, A5& vl, WK& wk) const
    {
      result_type info = 0;
      char jobvr = 'V';
      char jobvl = 'V';
      nt2_la_int n = nt2::width(a);
      BOOST_ASSERT_MSG(  (n == nt2_la_int(nt2::height(a)))
                         &&(n == nt2_la_int(nt2::height(b))) , "inputs must be square");
      nt2_la_int lda  = nt2::max(a.leading_size(), One<size_t>());
      nt2_la_int ldb  = nt2::max(b.leading_size(), One<size_t>());
      nt2_la_int wn = wk.main_need();
      wk.resize_main(wn);
      wk.resize_reals(8*n);
      vr.resize(of_size(n, n));
      vl.resize(of_size(n, n));
      nt2_la_int ldvl = vl.leading_size();
      nt2_la_int ldvr = vr.leading_size();
      NT2_F77NAME(cggev) ( &jobvl, &jobvr
                         , &n
                         , a.raw(), &lda
                         , b.raw(), &ldb
                         , alpha.raw()
                         , beta.raw()
                         , vl.raw(), &ldvl
                         , vr.raw(), &ldvr
                         , wk.main(), &wn
                         , wk.reals()
                         , &info);
      return info;
    }
  };
} }

#endif
