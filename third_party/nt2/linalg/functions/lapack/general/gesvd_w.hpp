//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVD_W_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESVD_W_HPP_INCLUDED

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
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //s
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s) const
     {
        result_type info;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1;
        nt2_la_int ldvt= 1;
        char job =  'N';

        NT2_F77NAME(dgesvd) (&job, &job, &m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), &info
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        nt2::gesvd_w(a0,s,w);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(WK)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //s
                              (unspecified_<WK>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, WK& w) const
     {
        result_type info;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1;
        nt2_la_int ldvt= 1;
        nt2_la_int wn = w.main_size();
        char job =  'N';
        NT2_F77NAME(dgesvd) ( &job, &job, &m, &n, a0.raw(), &ld, s.raw(), 0, &ldu
                            , 0, &ldvt, w.main()
                            , &wn, &info
                            );
        return info;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //s
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s) const
     {
        result_type info;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1 ;
        nt2_la_int ldvt= 1 ;
        char job =  'N';

        NT2_F77NAME(sgesvd) (&job, &job, &m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), &info
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        nt2::gesvd_w(a0,s,w);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(WK)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //s
                              (unspecified_<WK>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, WK& w) const
     {
        result_type info;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1;
        nt2_la_int ldvt= 1;
        nt2_la_int  wn = w.main_size();
        char job =  'N';

        NT2_F77NAME(sgesvd) ( &job, &job, &m, &n, a0.raw(), &ld, s.raw(), 0, &ldu
                            , 0, &ldvt, w.main()
                            , &wn, &info
                            );
        return info;
     }
  };

//---------------------------------------------Complex------------------------------------------------//

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))            //s
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s) const
     {
        result_type info;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1;
        nt2_la_int ldvt= 1;
        char job =  'N';

        NT2_F77NAME(cgesvd) (&job, &job, &m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), 0, &info
                            );

        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        w.resize_reals(5*std::min(m, n));
        nt2::gesvd_w(a0,s,w);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(WK)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))            //s
                              (unspecified_<WK>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, WK& w) const
     {
        result_type info;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1 ;
        nt2_la_int ldvt= 1 ;
        nt2_la_int  wn = w.main_size();
        char job =  'N';

        NT2_F77NAME(cgesvd) ( &job, &job, &m, &n, a0.raw(), &ld, s.raw(), 0, &ldu
                            , 0, &ldvt, w.main()
                            , &wn, w.reals(), &info
                            );
        return info;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))            //s
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s) const
     {
        result_type info;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1 ;
        nt2_la_int ldvt= 1 ;
        char job =  'N';

        NT2_F77NAME(zgesvd) (&job, &job, &m, &n, 0, &ld, 0, 0, &ldu
                            , 0, &ldvt, w.main()
                            , details::query(), 0, &info
                            );
        w.prepare_main();
        w.resize_main(5*nt2::max(m, n));
        w.resize_reals(5*std::min(m, n));
        nt2::gesvd_w(a0,s,w);

        return info;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesvd_w_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(WK)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> >, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >))            //s
                              (unspecified_<WK>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& s, WK& w) const
     {
        result_type info;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int ldu = 1 ;
        nt2_la_int ldvt= 1 ;
        nt2_la_int wn = w.main_size();
        char job =  'N';

        NT2_F77NAME(zgesvd) ( &job,&job,&m, &n, a0.raw(), &ld, s.raw(), 0, &ldu
                            , 0, &ldvt, w.main()
                            , &wn, w.reals(), &info
                            );
        return info;
     }
  };
} }

#endif
