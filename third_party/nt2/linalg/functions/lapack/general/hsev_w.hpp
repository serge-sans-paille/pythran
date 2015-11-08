//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HSEV_W_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_HSEV_W_HPP_INCLUDED

#include <nt2/linalg/functions/hsev_w.hpp>
#include <nt2/linalg/details/lapack/declare/hsev.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-double------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //w
                              (scalar_< ints8_<C0> >)                             //uplo
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo) const
     {
       result_type info;
       char jobz = 'N';
       details::workspace<typename A0::value_type> wk;
       nt2_la_int n = nt2::width(a);
       BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
       nt2_la_int lda = a.leading_size();

       NT2_F77NAME(dsyev) ( &jobz, &uplo, &n, 0, &lda, 0, wk.main(), details::query(), &info);
       wk.prepare_main();
       info = nt2::hsev_w(a, w, uplo, wk);

       return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //w
                              (scalar_< ints8_<C0> >)                             //uplo
                              (unspecified_<WK>)                                  //workspace
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo, WK& wk) const
     {
        result_type info;
        char jobz = 'N';
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        nt2_la_int  wn = wk.main_size();
        NT2_F77NAME(dsyev) (&jobz, &uplo, &n, a.raw(), &lda, w.raw(), wk.main(), &wn, &info);

        return info;
     }
  };

//---------------------------------------------Real-single------------------------------------------------//
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //w
                              (scalar_< ints8_<C0> >)                             //uplo
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo) const
     {
        result_type info;
        char jobz = 'N';
        details::workspace<typename A0::value_type> wk;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        NT2_F77NAME(ssyev) (&jobz, &uplo, &n, 0, &lda, 0, wk.main(), details::query()
                           , &info);

        wk.prepare_main();
        info = nt2::hsev_w(a, w, uplo, wk);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //w
                              (scalar_< ints8_<C0> >)                             //uplo
                              (unspecified_<WK>)                                  //workspace
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo, WK& wk) const
     {
        result_type info;
        char jobz = 'N';
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        nt2_la_int  wn = wk.main_size();
        NT2_F77NAME(ssyev) (&jobz, &uplo, &n, a.raw(), &lda, w.raw(), wk.main(), &wn, &info);

        return info;
     }
  };


//---------------------------------------------Complex-single------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))//a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))           //w
                              (scalar_< ints8_<C0> >)                                    //uplo
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo) const
     {
        result_type info;
        char jobz = 'N';
        details::workspace<typename A0::value_type> wk;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        NT2_F77NAME(cheev) (&jobz, &uplo, &n, 0, &lda, 0, wk.main(), details::query(), wk.reals(), &info);

        wk.prepare_main();
        wk.resize_reals(std::max(3*n-2, 1));
        info = nt2::hsev_w(a, w, uplo, wk);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >))//a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))           //w
                              (scalar_< ints8_<C0> >)                                    //uplo
                              (unspecified_<WK>)                                           //wk
                            )
  {
     typedef nt2_la_int result_type;


     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo, WK& wk) const
     {
        result_type info;
        char jobz = 'N';
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        nt2_la_int  wn = wk.main_size();
        NT2_F77NAME(cheev) (&jobz, &uplo, &n, a.raw(), &lda, w.raw(), wk.main(), &wn, wk.reals()
                           , &info);

        return info;
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))//a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))           //w
                              (scalar_< ints8_<C0> >)                                    //uplo
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo) const
     {
        result_type info;
        char jobz = 'N';
        details::workspace<typename A0::value_type> wk;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        NT2_F77NAME(zheev) (&jobz, &uplo, &n, 0, &lda, 0, wk.main(), details::query(), wk.reals()
                           , &info);

        wk.prepare_main();
        wk.resize_reals(std::max(3*n-2, 1));
        info = nt2::hsev_w(a, w, uplo, wk);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hsev_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >))//a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))           //w
                              (scalar_< ints8_<C0> >)                                    //uplo
                              (unspecified_<WK>)                                           //wk
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& w, C0 uplo, WK& wk) const
     {
        result_type info;
        char jobz = 'N';
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = a.leading_size();

        nt2_la_int  wn = wk.main_size();
        NT2_F77NAME(zheev) (&jobz, &uplo, &n, a.raw(), &lda, w.raw(), wk.main(), &wn, wk.reals()
                           , &info);

        return info;
     }
  };
} }

#endif
