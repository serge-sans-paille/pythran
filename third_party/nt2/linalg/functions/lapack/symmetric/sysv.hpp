//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_SYSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_SYSV_HPP_INCLUDED

#include <nt2/linalg/functions/sysv.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dsysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , double* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , double* b                , const nt2_la_int* ldb
                          , double* work             , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(ssysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , float* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , float* b                 , const nt2_la_int* ldb
                          , float* work              , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zsysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , nt2_la_complex* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , nt2_la_complex* b        , const nt2_la_int* ldb
                          , nt2_la_complex* work     , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(csysv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , nt2_la_complex* a
                          , const nt2_la_int* lda    , nt2_la_int* ipiv
                          , nt2_la_complex* b        , const nt2_la_int* ldb
                          , nt2_la_complex* work     , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(dsysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::sysv(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))  // B
                              (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& w) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = w.main_size();


        NT2_F77NAME(dsysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a2.raw()
                           , &ldb, w.main(), &wn, &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(ssysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::sysv(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))  // B
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& w) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(ssysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a2.raw()
                           , &ldb, w.main(), &wn, &that
                            );
        return that;
     }
  };

//--------------------------------------------Complex-----------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(zsysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::sysv(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))  // B
                              (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = a3.main_size();

        NT2_F77NAME(zsysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a2.raw()
                           , &ldb, a3.main(), &wn, &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))  // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';

        NT2_F77NAME(csysv) (&uplo, &n, &nhrs, 0, &ld, 0, 0, &ldb, w.main()
                            , details::query(), &that
                            );

          w.prepare_main();
          nt2::sysv(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sysv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))  // B
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int  nhrs = nt2::width(a2);
        char uplo = 'L';
        nt2_la_int  wn = a3.main_size();

        NT2_F77NAME(csysv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), a2.raw()
                           , &ldb, a3.main(), &wn, &that
                            );
        return that;
     }
  };
} }

#endif
