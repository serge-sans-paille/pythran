//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEBAL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEBAL_HPP_INCLUDED

#include <nt2/linalg/functions/gebal.hpp>
#include <nt2/linalg/details/lapack/declare/gebal.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-double------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebal_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(A3)(C0)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //scale
                              (scalar_< integer_<A2> >)                           //ilo
                              (scalar_< integer_<A3> >)                           //ihi
                              (scalar_< ints8_<C0> >)                             //job
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& scale
                                             , A2& ilo, A3& ihi, C0 job) const
     {
        result_type info;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        NT2_F77NAME(dgebal) (&job, &n
                            , a.raw(), &lda
                            , &ilo, &ihi
                            , scale.raw(), &info);
        return info;
     }
  };

//---------------------------------------------Real-single------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebal_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(A3)(C0)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //scale
                              (scalar_< integer_<A2> >)                           //ilo
                              (scalar_< integer_<A3> >)                           //ihi
                              (scalar_< ints8_<C0> >)                             //job
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& scale
                                             , A2& ilo, A3& ihi, C0 job) const
     {
        result_type info;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        NT2_F77NAME(sgebal) (&job, &n
                            , a.raw(), &lda
                            , &ilo, &ihi
                            , scale.raw(), &info);
        return info;
     }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebal_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(A3)(C0)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> > , S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //scale
                              (scalar_< integer_<A2> >)                           //ilo
                              (scalar_< integer_<A3> >)                           //ihi
                              (scalar_< ints8_<C0> >)                             //job
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& scale
                                             , A2& ilo, A3& ihi, C0 job) const
     {
        result_type info;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        NT2_F77NAME(cgebal) (&job, &n
                            , a.raw(), &lda
                            , &ilo, &ihi
                            , scale.raw(), &info);
        return info;
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebal_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(A3)(C0)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> > , S0 >)) //a
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //scale
                              (scalar_< integer_<A2> >)                           //ilo
                              (scalar_< integer_<A3> >)                           //ihi
                              (scalar_< ints8_<C0> >)                             //job
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& a, A1& scale
                                             , A2& ilo, A3& ihi, C0 job) const
     {
        result_type info = 0;
        nt2_la_int  n   = nt2::width(a);
        BOOST_ASSERT_MSG(n == nt2_la_int(nt2::height(a)), "input must be square");
        nt2_la_int  lda = nt2::max(a.leading_size(), One<size_t>());
        NT2_F77NAME(zgebal) (&job, &n
                            , a.raw(), &lda
                            , &ilo, &ihi
                            , scale.raw(), &info);
        return info;
     }
  };


} }

#endif
