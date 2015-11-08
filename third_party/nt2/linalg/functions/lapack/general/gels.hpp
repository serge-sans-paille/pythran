//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GELS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GELS_HPP_INCLUDED

#include <nt2/linalg/functions/gels.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

extern "C"
{
  void NT2_F77NAME(dgels)(  const char* trans      , const nt2_la_int* m
       ,  const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , double* a
                         ,  const nt2_la_int* lda  , double* b
                         ,  const nt2_la_int* ldb
                         ,  double* work           , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(sgels)(  const char* trans      , const nt2_la_int* m
       ,  const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , float* a
                         ,  const nt2_la_int* lda  , float* b
                         ,  const nt2_la_int* ldb
                         ,  float* work            , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(cgels)(  const char* trans      , const nt2_la_int* m
       ,  const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , nt2_la_complex* a
                         ,  const nt2_la_int* lda  , nt2_la_complex* b
                         ,  const nt2_la_int* ldb
                         ,  nt2_la_complex* work   , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );

  void NT2_F77NAME(zgels)(  const char* trans      , const nt2_la_int* m
       ,  const nt2_la_int* n
                         ,  const nt2_la_int* nhrs , nt2_la_complex* a
                         ,  const nt2_la_int* lda  , nt2_la_complex* b
                         ,  const nt2_la_int* ldb
                         ,  nt2_la_complex* work   , const nt2_la_int* lwork
                         ,  nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb  = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(dgels) (&trans, &m, &n, &nhrs, 0, &ld, 0, &ldb
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gels(a0,a1,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(dgels) (&trans, &m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.main()
                            , &wn, &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(sgels) (&trans, &m, &n, &nhrs, 0, &ld, 0, &ldb
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gels(a0,a1,w);

        return that;
     }
};


  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        char trans = 'N';


        NT2_F77NAME(sgels) (&trans, &m, &n, &nhrs, a0.raw(), &ld, a1.raw(),  &ldb
                            , a2.main()
                            , &wn, &that
                            );

        return that;
     }
  };

//-----------------------------Complex-----------------------------------------//

 /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb  = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(zgels) (&trans, &m, &n, &nhrs, 0, &ld, 0, &ldb
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gels(a0,a1,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(zgels) (&trans, &m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.main()
                            , &wn, &that
                            );

        return that;
     }
  };

 /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        details::workspace<typename A0::value_type> w;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb  = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(cgels) (&trans, &m, &n, &nhrs, 0, &ld, 0, &ldb
                            , w.main(), details::query(), &that
                            );

          w.prepare_main();
          nt2::gels(a0,a1,w);

        return that;
     }
  };

  /// INTERNAL ONLY - Workspace is ready
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gels_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))
                             (unspecified_<A2>)
                            )
  {
     typedef nt2_la_int result_type;
     typedef typename A0::value_type T ;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1,A2& a2) const
     {
        result_type that;
        nt2_la_int  m  = nt2::height(a0);
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  wn = a2.main_size();
        nt2_la_int  nhrs = nt2::width(a1);
        nt2_la_int  ldb = a1.leading_size();
        char trans = 'N';

        NT2_F77NAME(cgels) (&trans, &m, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                            , a2.main()
                            , &wn, &that
                            );

        return that;
     }
  };
}
}
#endif
