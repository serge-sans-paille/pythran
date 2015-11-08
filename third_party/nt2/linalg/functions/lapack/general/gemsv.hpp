//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEMSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEMSV_HPP_INCLUDED

#include <nt2/linalg/functions/gemsv.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

#include <nt2/sdk/meta/as_real.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

extern "C"
{
  void NT2_F77NAME(zcgesv)( const nt2_la_int* n    , const nt2_la_int* nrhs
                         , nt2_la_complex* a       , const nt2_la_int* lda
                         , nt2_la_int* ipiv        , const nt2_la_complex* b
                         , const nt2_la_int* ldb   , nt2_la_complex* x
                         , const nt2_la_int* ldx   , nt2_la_complex* work
                         , nt2_la_complex* swork   , double* rwork
                         , nt2_la_int* iter        , nt2_la_int* info
                         );

  void NT2_F77NAME(dsgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , double* a           , const nt2_la_int* lda
                         , nt2_la_int* ipiv
                         , const double* b     , const nt2_la_int* ldb
                         , double* x           , const nt2_la_int* ldx
                         , double* work        , float* swork
                         , nt2_la_int* iter    , nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gemsv_, tag::cpu_
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
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int iter,info;

        nt2::memory::container<tag::table_, f_t, nt2::_2D> swork(nt2::of_size(n*(n+nhrs),1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        w.resize_main(n*nhrs);

        NT2_F77NAME(dsgesv)( &n, &nhrs, a0.raw(), &lda, ipiv.raw() , a1.raw()
                           , &ldb, a2.raw(), &ldb , w.main(), swork.raw()
                           , &iter, &info
                           );
        return iter;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gemsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >)) // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >)) // B
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >)) // X
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type v_t;
     typedef typename boost::dispatch::meta::downgrade<v_t>::type f_t;
     typedef typename nt2::meta::as_real<f_t>::type   r_t;
     typedef typename nt2::meta::as_real<v_t>::type   d_t;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1, A2& a2) const
     {
        details::workspace<typename A2::value_type> w;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int iter,info;

        nt2::memory::container<tag::table_, f_t, nt2::_2D> swork(nt2::of_size(n*(n+nhrs),1));
        nt2::memory::container<tag::table_, d_t, nt2::_2D> rwork(nt2::of_size(n,1));
        nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> ipiv(nt2::of_size(n,1));
        w.resize_main(n*nhrs);

        NT2_F77NAME(zcgesv)( &n, &nhrs, a0.raw(), &lda, ipiv.raw() , a1.raw()
                           , &ldb, a2.raw(), &ldb , w.main(), swork.raw()
                           , rwork.raw(), &iter, &info
                           );
        return iter;
     }
  };

} }

#endif
