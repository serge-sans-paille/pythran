//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POMSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POMSV_HPP_INCLUDED

#include <nt2/linalg/functions/pomsv.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/sdk/meta/as_real.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

extern "C"
{
  void NT2_F77NAME(dsposv)( const char* uplo
                          , const nt2_la_int* n , const nt2_la_int* nrhs
                          , double* a          , const nt2_la_int* lda
                          , const double* b     , const nt2_la_int* ldb
                          , double* x           , const nt2_la_int* ldx
                          , double* work        , float* swork
                          , nt2_la_int* iter    , nt2_la_int* info
                         );

  void NT2_F77NAME(zcposv)( const char* uplo
                          , const nt2_la_int* n     , const nt2_la_int* nrhs
                          , nt2_la_complex* a       , const nt2_la_int* lda
                          , const nt2_la_complex* b , const nt2_la_int* ldb
                          , nt2_la_complex* x       , const nt2_la_int* ldx
                          , nt2_la_complex* work    , nt2_la_complex* swork
                          , double* rwork
                          , nt2_la_int* iter    , nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pomsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >)) // A
                              ((container_< nt2::tag::table_, double_<A1>, S1 >)) // B
                              ((container_< nt2::tag::table_, double_<A2>, S2 >)) // X
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename boost::dispatch::meta::downgrade<v_t>::type f_t;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1, A2& a2) const
     {
        details::workspace<typename A2::value_type> w;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int iter,info;
        char uplo = 'L';

        nt2::memory::container<tag::table_, f_t, nt2::_2D> swork(nt2::of_size(n*(n+nhrs),1));
        w.resize_main(n*nhrs);

        NT2_F77NAME(dsposv)( &uplo, &n, &nhrs, a0.raw(), &lda, a1.raw()
                           , &ldb, a2.raw(), &ldb , w.main(), swork.raw()
                           , &iter, &info
                           );
        return iter;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pomsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >)) // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >)) // B
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >)) // X
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename boost::dispatch::meta::downgrade<v_t>::type f_t;
     typedef typename nt2::meta::as_real<v_t>::type   r_t;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1, A2& a2) const
     {
        details::workspace<typename A2::value_type> w;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();
        nt2_la_int iter,info;
        char uplo = 'L';

        nt2::memory::container<tag::table_, r_t, nt2::_2D> rwork(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, f_t, nt2::_2D> swork(nt2::of_size(n*(n+nhrs),1));
        w.resize_main(n*nhrs);

        NT2_F77NAME(zcposv)( &uplo, &n, &nhrs, a0.raw(), &lda, a1.raw()
                           , &ldb, a2.raw(), &ldb , w.main(), swork.raw()
                           , rwork.raw(), &iter, &info
                           );
        return iter;
     }
  };
} }

#endif
