//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_SYCON_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_SYCON_HPP_INCLUDED

#include <nt2/linalg/functions/sycon.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/sdk/meta/as_real.hpp>
extern "C"
{
  void NT2_F77NAME(dsycon)( const char* uplo     , const nt2_la_int* n
                          , const double* a      , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const double* anorm  , double* rcond
                          , double* work         , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(ssycon)( const char* uplo     , const nt2_la_int* n
                          , const float* a       , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const float* anorm   , float* rcond
                          , float* work          , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zsycon)( const char* uplo        , const nt2_la_int* n
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const double* anorm     , double* rcond
                          , nt2_la_complex* work
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(csycon)( const char* uplo        , const nt2_la_int* n
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , const float* anorm      , float* rcond
                          , nt2_la_complex* work
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef typename A0::value_type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(2*n,1));
      nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(dsycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(2*n,1));
      nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D>  iwork(nt2::of_size(n,1));

      NT2_F77NAME(ssycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), iwork.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef typename A0::value_type  v_t;
    typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::memory::container<tag::table_, v_t, nt2::_2D> work(nt2::of_size(2*n,1));

      NT2_F77NAME(zsycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), &info
                          );

      return rcond;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sycon_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (scalar_< floating_<A2> >)            //  anorm
                            )
  {
    typedef typename A0::value_type v_t;
    typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      result_type rcond;
      nt2_la_int n = nt2::height(a0);
      nt2_la_int ld = n;
      nt2_la_int info;
      char uplo = 'L';

      nt2::memory::container<tag::table_, v_t, nt2::_2D> work(nt2::of_size(2*n,1));

      NT2_F77NAME(csycon) ( &uplo, &n, a0.raw(), &ld, a1.raw(), &a2, &rcond
                          , work.raw(), &info
                          );

      return rcond;
    }
  };
} }

#endif
