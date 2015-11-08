//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVD_HPP_INCLUDED

#include <nt2/linalg/functions/gesvd.hpp>
#include <nt2/linalg/details/lapack/declare/gesvd.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //s
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >)) //u
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                             //jobu
                              (scalar_< ints8_<A5> >)                             //jobvt

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 jobu, A5 jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;


        NT2_F77NAME(dgesvd) (&jobu,&jobvt,&m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), &that
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //s
                              ((container_<nt2::tag::table_,  double_<A2>, S2 >)) //u
                              ((container_<nt2::tag::table_,  double_<A3>, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                             //jobu
                              (scalar_< ints8_<A5> >)                             //jobvt
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 jobu, A5 jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int wn = w.main_size();
        NT2_F77NAME(dgesvd) ( &jobu,&jobvt,&m, &n, a0.raw(), &ld, s.raw(), u.raw(), &ldu
                            , vt.raw(), &ldvt, w.main()
                            , &wn, &that
                            );
        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //s
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >)) //u
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                             //jobu
                              (scalar_< ints8_<A5> >)                             //jobvt

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 jobu, A5 jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;

        NT2_F77NAME(sgesvd) (&jobu,&jobvt,&m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), &that
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //s
                              ((container_<nt2::tag::table_,  single_<A2>, S2 >)) //u
                              ((container_<nt2::tag::table_,  single_<A3>, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                             //jobu
                              (scalar_< ints8_<A5> >)                             //jobvt
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 jobu, A5 jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(sgesvd) ( &jobu,&jobvt,&m, &n, a0.raw(), &ld, s.raw(), u.raw(), &ldu
                            , vt.raw(), &ldvt, w.main()
                            , &wn, &that
                            );
        return that;
     }
  };

//---------------------------------------------Complex------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))            //s
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                                        //jobu
                              (scalar_< ints8_<A5> >)                                        //jobvt

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 jobu, A5 jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;

        NT2_F77NAME(cgesvd) (&jobu,&jobvt,&m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), 0, &that
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        w.resize_reals(5*std::min(m, n));
        nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))            //s
                              ((container_<nt2::tag::table_,  complex_<single_<A2> >, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<single_<A3> >, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                                        //jobu
                              (scalar_< ints8_<A5> >)                                        //jobvt
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 jobu, A5 jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int  wn = w.main_size();

        NT2_F77NAME(cgesvd) ( &jobu,&jobvt,&m, &n, a0.raw(), &ld, s.raw(), u.raw(), &ldu
                            , vt.raw(), &ldvt, w.main()
                            , &wn, w.reals(), &that
                            );
        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))            //s
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                                        //jobu
                              (scalar_< ints8_<A5> >)                                        //jobvt

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, A2& u,A3 &vt, A4 jobu, A5 jobvt) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;

        NT2_F77NAME(zgesvd) (&jobu,&jobvt,&m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), 0, &that
                            );
        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        w.resize_reals(5*std::min(m, n));
        nt2::gesvd(a0,s,u,vt,jobu,jobvt,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)(S3)(A4)(A5)(A6)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))            //s
                              ((container_<nt2::tag::table_,  complex_<double_<A2> >, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<double_<A3> >, S3 >)) //vt
                              (scalar_< ints8_<A4> >)                                        //jobu
                              (scalar_< ints8_<A5> >)                                        //jobvt
                              (unspecified_<A6>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s,A2& u, A3& vt, A4 jobu, A5 jobvt, A6& w) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = u.leading_size() > 1 ? u.leading_size() : 1 ;
        nt2_la_int ldvt= vt.leading_size() > 1 ? vt.leading_size() : 1 ;
        nt2_la_int wn = w.main_size();

        NT2_F77NAME(zgesvd) ( &jobu,&jobvt,&m, &n, a0.raw(), &ld, s.raw(), u.raw(), &ldu
                            , vt.raw(), &ldvt, w.main()
                            , &wn, w.reals(), &that
                            );
        return that;
     }
  };
} }

#endif
