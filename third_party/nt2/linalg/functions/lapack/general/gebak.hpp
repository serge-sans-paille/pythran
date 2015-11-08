//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEBAK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GEBAK_HPP_INCLUDED

#include <nt2/linalg/functions/gebak.hpp>
#include <nt2/linalg/details/lapack/declare/gebak.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-double------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebak_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(C1)(C2)(C3)
                            , ((container_<nt2::tag::table_,  double_<A0>, S0 >)) //v
                              ((container_<nt2::tag::table_,  double_<A1>, S1 >)) //scale
                              (scalar_< integer_<C0> >)                           //ilo
                              (scalar_< integer_<C1> >)                           //ihi
                              (scalar_< ints8_<C2> >)                             //job
                              (scalar_< ints8_<C3> >)                             //side
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& v,A1 const& scale
                                             , C0 const& ilo, C1 const& ihi
                                             , C2 job, C3 side) const
     {
        result_type info;
        nt2_la_int  n = nt2::height(v);
        nt2_la_int  m = nt2::width(v);
        nt2_la_int  ldv = nt2::max(v.leading_size(), One<size_t>());
        NT2_F77NAME(dgebak) (&job, &side, &n
                            , &ilo, &ihi
                            , scale.raw(), &m, v.raw()
                            , &ldv, &info);
        return info;
     }
  };

//---------------------------------------------Real-single------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebak_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(C1)(C2)(C3)
                            , ((container_<nt2::tag::table_,  single_<A0>, S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >)) //scale
                              (scalar_< integer_<C0> >)                           //ilo
                              (scalar_< integer_<C1> >)                           //ihi
                              (scalar_< ints8_<C2> >)                             //job
                              (scalar_< ints8_<C3> >)                             //side
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& v,A1 const& scale
                                             , C0 const& ilo, C1 const& ihi
                                             , C2 job, C3 side) const
     {
        result_type info;
        nt2_la_int n = nt2::height(v);
        nt2_la_int m = nt2::width(v);
        nt2_la_int  ldv = nt2::max(v.leading_size(), One<size_t>());
        NT2_F77NAME(sgebak) (&job, &side, &n
                            , &ilo, &ihi
                            , scale.raw(), &m, v.raw()
                            , &ldv, &info);
        return info;
     }
  };

//---------------------------------------------Complex-single------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebak_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(C1)(C2)(C3)
                            , ((container_<nt2::tag::table_,  complex_<single_<A0> > , S0 >)) //a
                              ((container_<nt2::tag::table_,  single_<A1>, S1 >))   //scale
                              (scalar_< integer_<C0> >)                             //ilo
                              (scalar_< integer_<C1> >)                             //ihi
                              (scalar_< ints8_<C2> >)                               //job
                              (scalar_< ints8_<C3> >)                               //side
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& v,A1 const& scale
                                             , C0 const& ilo, C1 const& ihi
                                             , C2 job, C3 side) const
     {
        result_type info;
        nt2_la_int n = nt2::height(v);
        nt2_la_int m = nt2::width(v);
        nt2_la_int  ldv = nt2::max(v.leading_size(), One<size_t>());
        NT2_F77NAME(cgebak) (&job, &side, &n
                            , &ilo, &ihi
                            , scale.raw(), &m, v.raw()
                            , &ldv, &info);
        return info;
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gebak_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(C0)(C1)(C2)(C3)
                            , ((container_<nt2::tag::table_,  complex_<double_<A0> > , S0 >)) //a
                               ((container_<nt2::tag::table_,  double_<A1>, S1 >))            //scale
                              (scalar_< integer_<C0> >)                                        //ilo
                              (scalar_< integer_<C1> >)                                       //ihi
                              (scalar_< ints8_<C2> >)                                         //job
                              (scalar_< ints8_<C3> >)                                         //side
                            )
  {
    typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()( A0& v,A1 const& scale
                                             , C0 const& ilo, C1 const& ihi
                                             , C2 job, C3 side) const
     {
        result_type info;
        nt2_la_int n = nt2::height(v);
        nt2_la_int m = nt2::width(v);
        nt2_la_int  ldv = nt2::max(v.leading_size(), One<size_t>());
        NT2_F77NAME(zgebak) (&job, &side, &n
                            , &ilo, &ihi
                            , scale.raw(), &m, v.raw()
                            , &ldv, &info);
        return info;
     }
  };

} }

#endif
