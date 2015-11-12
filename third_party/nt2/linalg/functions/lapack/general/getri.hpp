//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GETRI_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GETRI_HPP_INCLUDED

#include <nt2/linalg/functions/getri.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dgetri)( const nt2_la_int* n
                          , double* a, const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , double* work, const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgetri)( const nt2_la_int* n
                          , float* a, const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , float* work, const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(cgetri)( const nt2_la_int* n
                          , nt2_la_complex* a, const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , nt2_la_complex* work, const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zgetri)( const nt2_la_int* n
                          , nt2_la_complex* a, const nt2_la_int* lda
                          , const nt2_la_int* ipiv
                          , nt2_la_complex* work, const nt2_la_int* lwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Use existing workspace
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1, A2& a2) const
    {
      result_type that;
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();
      nt2_la_int  wn = a2.main_size();

      // Perform computation
      NT2_F77NAME(dgetri) ( &n, a0.raw(), &ld, a1.raw()
                          , a2.main(), &wn
                          , &that
                          );

      return that;
    }
  };
  /// INTERNAL ONLY - Use existing workspace
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1, A2& a2) const
    {
      result_type that;
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();
      nt2_la_int  wn = a2.main_size();

      // Perform computation
      NT2_F77NAME(sgetri) ( &n, a0.raw(), &ld, a1.raw()
                          , a2.main(), &wn
                          , &that
                          );

      return that;
    }
  };

  /// INTERNAL ONLY - Use existing workspace
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1, A2& a2) const
    {
      result_type that;
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();
      nt2_la_int  wn = a2.main_size();

      // Perform computation
      NT2_F77NAME(cgetri) ( &n, a0.raw(), &ld, a1.raw()
                          , a2.main(), &wn
                          , &that
                          );

      return that;
    }
  };

  /// INTERNAL ONLY - Use existing workspace
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                              (unspecified_<A2>)
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1, A2& a2) const
    {
      result_type that;
      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();
      nt2_la_int  wn = a2.main_size();

      // Perform computation
      NT2_F77NAME(zgetri) ( &n, a0.raw(), &ld, a1.raw()
                          , a2.main(), &wn
                          , &that
                          );

      return that;
    }
  };

  /// INTERNAL ONLY - COmpute workspace then perform actions
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                            )
  {
    typedef nt2_la_int result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
    {
      result_type that;
      details::workspace<typename A0::value_type> w;

      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();

      // How much memory do I need ?
      NT2_F77NAME(dgetri) ( &n, a0.raw(), &ld
                          , a1.raw(), w.main(), details::query()
                          , &that
                          );

      // Adjust workspace & compute
      w.prepare_main();
      nt2::getri(a0,a1,w);

      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
      result_type that;
      details::workspace<typename A0::value_type> w;

      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();

      // How much memory do I need ?
      NT2_F77NAME(sgetri) ( &n, a0.raw(), &ld
                          , a1.raw(), w.main(), details::query()
                          , &that
                          );

      // Adjust workspace & compute
      w.prepare_main();
      nt2::getri(a0,a1,w);

      return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
      result_type that;
      details::workspace<typename A0::value_type> w;

      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();

      // How much memory do I need ?
      NT2_F77NAME(zgetri) ( &n, a0.raw(), &ld
                          , a1.raw(), w.main(), details::query()
                          , &that
                          );

      // Adjust workspace & compute
      w.prepare_main();
      nt2::getri(a0,a1,w);

      return that;
     }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::getri_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >))
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
      result_type that;
      details::workspace<typename A0::value_type> w;

      nt2_la_int  n  = nt2::width(a0);
      nt2_la_int  ld = a0.leading_size();

      // How much memory do I need ?
      NT2_F77NAME(cgetri) ( &n, a0.raw(), &ld
                          , a1.raw(), w.main(), details::query()
                          , &that
                          );

      // Adjust workspace & compute
      w.prepare_main();
      nt2::getri(a0,a1,w);

      return that;
     }
  };
} }

#endif
