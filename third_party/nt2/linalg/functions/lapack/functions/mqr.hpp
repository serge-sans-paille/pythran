//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_MQR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_MQR_HPP_INCLUDED

#include <nt2/linalg/functions/mqr.hpp>
#include <nt2/linalg/details/lapack/declare/mqr.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/numeric_class.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/eye.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';


        NT2_F77NAME(dormqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();
        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(dormqr) ( &side, &trans, &m, &m, &k, a0.raw(), &ld, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };

   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(sormqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();

        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        //nt2_la_int  n  = nt2::width(a0);
        //nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(sormqr) ( &side, &trans, &m, &m, &k, a0.raw(), &m, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };

//------------------------------------------Complex----------------------------------//


   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(cunmqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();

        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        //nt2_la_int  n  = nt2::width(a0);
        //nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(cunmqr) ( &side, &trans, &m, &m, &k, a0.raw(), &m, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };

   /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        details::workspace<typename A2::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(zunmqr) (&side,&trans,&m, &m, &k, 0, &ld, 0, 0, &m, w.main()
                            , details::query(), &that
                            );
        w.prepare_main();

        nt2::mqr(a0,a1,a2,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mqr_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)(A3)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))
                             (unspecified_<A3>)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2,A3& a3) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        //nt2_la_int  n  = nt2::width(a0);
        //nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a3.main_size();
        nt2_la_int  k  = a1.leading_size();
        char side  = 'L';
        char trans = 'N';

        NT2_F77NAME(zunmqr) ( &side, &trans, &m, &m, &k, a0.raw(), &m, a1.raw()
                            , a2.raw(), &m, a3.main(), &wn, &that
                            );
        return that;
     }
  };
} }

#endif
