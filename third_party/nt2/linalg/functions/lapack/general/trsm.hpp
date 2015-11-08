//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_TRSM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_TRSM_HPP_INCLUDED

#include <nt2/linalg/functions/trsm.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <complex>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, double_<A4>, S4 >))
                              ((container_< nt2::tag::table_, double_<A5>, S5 >))
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;

        double  alpha = 1;

        NT2_F77NAME(dtrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, single_<A4>, S4 >))
                              ((container_< nt2::tag::table_, single_<A5>, S5 >))
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;
        float  alpha = 1;

        NT2_F77NAME(strsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, complex_<double_<A4> >, S4 >))
                              ((container_< nt2::tag::table_, complex_<double_<A5> >, S5 >))
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;
        std::complex<double> alpha(1.0,0.);

        NT2_F77NAME(ztrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, complex_<single_<A4> >, S4 >))
                              ((container_< nt2::tag::table_, complex_<single_<A5> >, S5 >))
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;
        std::complex<float> alpha(1.0,0.);

        NT2_F77NAME(ctrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)(A6)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, double_<A4>, S4 >))
                              ((container_< nt2::tag::table_, double_<A5>, S5 >))
                              (scalar_< floating_<A6> >)
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b, A6 const alpha
                                              ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;

        NT2_F77NAME(dtrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)(A6)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, single_<A4>, S4 >))
                              ((container_< nt2::tag::table_, single_<A5>, S5 >))
                              (scalar_< floating_<A6> >)
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b, A6 const alpha ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;

        NT2_F77NAME(strsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)(A6)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, complex_<double_<A4> >, S4 >))
                              ((container_< nt2::tag::table_, complex_<double_<A5> >, S5 >))
                              (scalar_< complex_<floating_<A6> > >)
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b, A6 const alpha
                                              ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;

        NT2_F77NAME(ztrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trsm_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(S4)(A5)(S5)(A6)
                            , (scalar_< ints8_<A0> >)
                              (scalar_< ints8_<A1> >)
                              (scalar_< ints8_<A2> >)
                              (scalar_< ints8_<A3> >)
                              ((container_< nt2::tag::table_, complex_<single_<A4> >, S4 >))
                              ((container_< nt2::tag::table_, complex_<single_<A5> >, S5 >))
                              (scalar_< complex_<floating_<A6> > >)
                            )
  {
    typedef void  result_type;

     BOOST_FORCEINLINE result_type operator()( A0 const& side, A1 const& uplo, A2 const& transa
                                             , A3 const& diag, A4 const& a, A5& b ,A6 const alpha
                                             ) const
     {
        nt2_la_int  m  = nt2::height(a);
        nt2_la_int  n  = nt2::width(b);
        nt2_la_int  lda = (side=='L'||'l')? m : n ;

        NT2_F77NAME(ctrsm)( &side, &uplo, &transa, &diag, &m, &n, &alpha
                          , a.raw(),&lda,b.raw(),&m);

     }
  };

} }

#endif
