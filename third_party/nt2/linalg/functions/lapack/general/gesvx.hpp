//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVX_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVX_HPP_INCLUDED

#include <nt2/linalg/functions/gesvx.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/sdk/meta/as_real.hpp>

extern "C"
{
  void NT2_F77NAME(dgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const double* a     , const nt2_la_int* lda
                          , double* af          , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , double* r           , double* c
                          , const double* b     , const nt2_la_int* ldb
                          , double* x           , const nt2_la_int* ldx
                          , double* rcond       , double* ferr
                          , double* berr        , double* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(sgesvx)( const char* fact    , const char* trans
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , const float* a      , const nt2_la_int* lda
                          , float* af           , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv    , const char* equed
                          , float* r            , float* c
                          , const float* b      , const nt2_la_int* ldb
                          , float* x            , const nt2_la_int* ldx
                          , float* rcond        , float* ferr
                          , float* berr         , float* work
                          , nt2_la_int* iwork   , nt2_la_int* info
                          );

  void NT2_F77NAME(cgesvx)( const char* fact        , const char* trans
                          , const nt2_la_int* n     , const nt2_la_int* nrhs
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_complex* af      , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv        , const char* equed
                          , float* r                , float* c
                          , const nt2_la_complex* b , const nt2_la_int* ldb
                          , nt2_la_complex* x       , const nt2_la_int* ldx
                          , float* rcond            , float* ferr
                          , float* berr             , nt2_la_complex* work
                          , float* rwork            , nt2_la_int* info
                          );

  void NT2_F77NAME(zgesvx)( const char* fact        , const char* trans
                          , const nt2_la_int* n     , const nt2_la_int* nrhs
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_complex* af      , const nt2_la_int* ldaf
                          , nt2_la_int* ipiv        , const char* equed
                          , double* r               , double* c
                          , const nt2_la_complex* b , const nt2_la_int* ldb
                          , nt2_la_complex* x       , const nt2_la_int* ldx
                          , double* rcond           , double* ferr
                          , double* berr            , nt2_la_complex* work
                          , double* rwork           , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_,  single_<A0>, S0 >))  //A
                              (( container_< nt2::tag::table_, single_<A1>, S1 >)) // B
                              ((container_< nt2::tag::table_,  single_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& rcond) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::memory::container<tag::table_, T, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> r(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> c(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(4*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> iwork(nt2::of_size(n,1));

        NT2_F77NAME(sgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_,  double_<A0>, S0 >))  //A
                              (( container_< nt2::tag::table_, double_<A1>, S1 >))  // B
                              ((container_< nt2::tag::table_,  double_<A2>, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& rcond) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::memory::container<tag::table_, T, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> r(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> c(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(4*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> iwork(nt2::of_size(n,1));

        NT2_F77NAME(dgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.main()
                           , iwork.raw() , &that
                           );

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  //A
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)          //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& rcond) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::memory::container<tag::table_, std::complex<T>, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> r(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> c(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> rwork(nt2::of_size(2*n,1));
        details::workspace<typename A2::value_type> work;
        work.resize_main(2*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));


        NT2_F77NAME(cgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.main()
                           , rwork.raw() , &that
                           );

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvx_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  //A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))  // B
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))  // X
                              (scalar_< floating_<A3> >)           //rcond
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type  T;

     BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2& a2, A3& rcond) const
     {
        result_type that;
        nt2_la_int  n  = nt2::height(a0);
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = n;
        char fact  = 'N';
        char trans = 'N';
        char equed = 'N';

        nt2::memory::container<tag::table_, std::complex<T>, nt2::_2D> af(nt2::of_size(n,n));

        nt2::memory::container<tag::table_, T, nt2::_2D> r(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> c(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> ferr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> berr(nt2::of_size(nhrs,1));
        nt2::memory::container<tag::table_, T, nt2::_2D> rwork(nt2::of_size(2*n,1));

        details::workspace<typename A2::value_type> work;
        work.resize_main(2*n);

        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));

        NT2_F77NAME(zgesvx)( &fact       , &trans
                           , &n          , &nhrs
                           , a0.raw()    , &n
                           , af.raw()    , &n
                           , ipiv.raw()  , &equed
                           , r.raw()     , c.raw()
                           , a1.raw()    , &ldb
                           , a2.raw()    , &ldb
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.main()
                           , rwork.raw() , &that
                           );

        return that;
     }
  };

} }

#endif
