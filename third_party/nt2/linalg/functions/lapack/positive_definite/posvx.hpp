//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POSVX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POSVX_HPP_INCLUDED

#include <nt2/linalg/functions/posvx.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/sdk/meta/as_real.hpp>


extern "C"
{
  void NT2_F77NAME(dposvx)( const char* fact    , const char* uplo
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const double* a     , const nt2_la_int* lda
                          , double* af          , const nt2_la_int* ldaf
                          , const char* equed   , double* s
                          , const double* b     , const nt2_la_int* ldb
                          , double* x           , const nt2_la_int* ldx
                          , double* rcond       , double* ferr
                          , double* berr        , double* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(sposvx)( const char* fact    , const char* uplo
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const float* a      , const nt2_la_int* lda
                          , float* af           , const nt2_la_int* ldaf
                          , const char* equed   , float* s
                          , const float* b      , const nt2_la_int* ldb
                          , float* x            , const nt2_la_int* ldx
                          , float* rcond        , float* ferr
                          , float* berr         , float* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(cposvx)( const char* fact        , const char* uplo
                          , const nt2_la_int* n     , const nt2_la_int* nrhs
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_complex* af      , const nt2_la_int* ldaf
                          , const char* equed       , float* s
                          , const nt2_la_complex* b , const nt2_la_int* ldb
                          , nt2_la_complex* x       , const nt2_la_int* ldx
                          , float* rcond            , float* ferr
                          , float* berr             , nt2_la_complex* work
                          , float* rwork            , nt2_la_int* info
                          );

  void NT2_F77NAME(zposvx)( const char* fact        , const char* uplo
                          , const nt2_la_int* n     , const nt2_la_int* nrhs
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_complex* af      , const nt2_la_int* ldaf
                          , const char* equed       , double* s
                          , const nt2_la_complex* b , const nt2_la_int* ldb
                          , nt2_la_complex* x       , const nt2_la_int* ldx
                          , double* rcond           , double* ferr
                          , double* berr            , nt2_la_complex* work
                          , double* rwork           , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))  // B
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char equed  = 'N';
        char uplo  = 'L';

        nt2::memory::container<tag::table_, T, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> s(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(3*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> iwork(nt2::of_size(n,1));

        NT2_F77NAME(dposvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , &equed      , s.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))  // B
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char uplo  = 'L';
        char equed = 'N';

        nt2::memory::container<tag::table_, T, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> s(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(3*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> iwork(nt2::of_size(n,1));

        NT2_F77NAME(sposvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , &equed      , s.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char uplo  = 'L';
        char equed = 'N';

        nt2::memory::container<tag::table_, v_t, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> s(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(2*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> rwork(nt2::of_size(n,1));

        NT2_F77NAME(zposvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , &equed      , s.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , rwork.raw() , &that
                           );

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& a3) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char uplo  = 'L';
        char equed = 'N';

        nt2::memory::container<tag::table_, v_t, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> s(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(2*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> rwork(nt2::of_size(n,1));

        NT2_F77NAME(cposvx)( &fact       , &uplo
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , &equed      , s.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &a3         , ferr.raw()
                           , berr.raw()  , work.main()
                           , rwork.raw() , &that
                           );

        return that;
     }
  };
} }

#endif
