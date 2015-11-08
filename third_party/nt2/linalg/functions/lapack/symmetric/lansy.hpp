//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_LANSY_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_SYMMETRIC_LANSY_HPP_INCLUDED

#include <nt2/linalg/functions/lange.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/meta/as_real.hpp>

extern "C"
{
  double NT2_F77NAME(dlansy)( const char* norm     , const char* uplo
                          , const nt2_la_int* n    , const double* a
                          , const nt2_la_int* lda  , double* work
                          );

  float NT2_F77NAME(slansy)( const char* norm      , const char* uplo
                          , const nt2_la_int* n    , const float* a
                          , const nt2_la_int* lda  , float* work
                          );

  double NT2_F77NAME(zlansy)( const char* norm     , const char* uplo
                          , const nt2_la_int* n    , const nt2_la_complex* a
                          , const nt2_la_int* lda  , double* work
                          );

  float NT2_F77NAME(clansy)( const char* norm      , const char* uplo
                          , const nt2_la_int* n    , const nt2_la_complex* a
                          , const nt2_la_int* lda  , float* work
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                              (unspecified_<nt2::symmetric_>)             //  norm
                            )
  {
    typedef typename A0::value_type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, nt2::symmetric_ const&) const
    {
      result_type norm;
      char uplo = 'L';
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = n;

     if(a1 =='I'|| a1 =='1'|| a1 =='O')
     {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(dlansy)( &a1, &uplo, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(dlansy)( &a1, &uplo, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                              (unspecified_<nt2::symmetric_>)             //  norm
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, nt2::symmetric_ const&) const
    {
      result_type norm;
      char uplo = 'L';
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = n;


      if(a1 =='I' || a1 =='1'|| a1 =='O')
      {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(slansy)( &a1, &uplo, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(slansy)( &a1, &uplo, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                              (unspecified_<nt2::symmetric_>)             //  norm
                            )
  {
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, nt2::symmetric_ const&) const
    {
      result_type norm;
      char uplo = 'L';
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = n;

     if(a1 =='I'|| a1 =='1'|| a1 =='O')
     {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(zlansy)( &a1, &uplo, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(zlansy)( &a1, &uplo, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                              (unspecified_<nt2::symmetric_>)             //  norm
                            )
  {
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1, nt2::symmetric_ const&) const
    {
      result_type norm;
      char uplo = 'L';
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = n;


      if(a1 =='I' || a1 =='1'|| a1 =='O')
      {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(n,1));
        norm = NT2_F77NAME(clansy)( &a1, &uplo, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(clansy)( &a1, &uplo, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };
} }

#endif
