//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GELSY_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GELSY_HPP_INCLUDED

#include <nt2/linalg/functions/gelsy.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/eps.hpp>

extern "C"
{
  void NT2_F77NAME(dgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , double* a
                         ,  const nt2_la_int* lda  , double* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const double* rcond    , nt2_la_int* rank
                         ,  double* work           , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(sgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , float* a
                         ,  const nt2_la_int* lda  , float* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const float* rcond     , nt2_la_int* rank
                         ,  float* work            , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(cgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , nt2_la_complex* a
                         ,  const nt2_la_int* lda  , nt2_la_complex* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const float* rcond     , nt2_la_int* rank
                         ,  nt2_la_complex* work   , const nt2_la_int* lwork
                         ,  float* rwork           , nt2_la_int* info
                         );

  void NT2_F77NAME(zgelsy)( const nt2_la_int* m    , const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , nt2_la_complex* a
                         ,  const nt2_la_int* lda  , nt2_la_complex* b
                         ,  const nt2_la_int* ldb  , nt2_la_int* jpvt
                         ,  const double* rcond    , nt2_la_int* rank
                         ,  nt2_la_complex* work   , const nt2_la_int* lwork
                         ,  double* rwork          , nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gelsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a2.leading_size();

        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), &that
                            );

        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &a3, w.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(dgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &rank, a3.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gelsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), &that
                            );

        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &a3, w.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;


        NT2_F77NAME(sgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &rank, a3.main()
                            , &wn, &that
                            );

        return that;
     }
  };

//-----------------------------Complex-----------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(cgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), 0, &that
                            );
        w.prepare_main();
        nt2::gelsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;
     typedef  float T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;
        nt2::container::table<T> rwork(nt2::of_size(2*n,1));

        NT2_F77NAME(cgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), rwork.raw(), &that
                            );

        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(cgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &a3, w.main()
                            , &wn, rwork.raw(), &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef float T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;
        nt2::container::table<T> rwork(nt2::of_size(2*n,1));

        NT2_F77NAME(cgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &rank, a3.main()
                            , &wn, rwork.raw(), &that
                            );

        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int rank;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        typedef double T ;

        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;

        NT2_F77NAME(zgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &rank
                            , w.main(), details::query(), 0, &that
                            );
          w.prepare_main();
          nt2::gelsy(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute with rank as output
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                              (scalar_< integer_<A3> > )   //rank
                            )
  {
     typedef nt2_la_int result_type;
     typedef  double T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        T rcond =  Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;
        nt2::container::table<T> rwork(nt2::of_size(2*n,1));

        NT2_F77NAME(zgelsy) (&m, &n, &nhrs, 0, &ld, 0, &ldb, 0, &rcond, &a3
                            , w.main(), details::query(), 0, &that
                            );

        w.prepare_main();
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(zgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &a3, w.main()
                            , &wn, rwork.raw(), &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gelsy_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                              (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef double T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int rank;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        T rcond = Sqrteps<T>() - (Sqrteps<T>() - Eps<T>())/2;
        nt2::container::table<T> rwork(nt2::of_size(2*n,1));

        NT2_F77NAME(zgelsy) (&m, &n, &nhrs, a0.raw(), &ld, a2.raw(), &ldb
                            , a1.raw(), &rcond, &rank, a3.main()
                            , &wn, rwork.raw(), &that
                            );

        return that;
     }
  };
} }

#endif
