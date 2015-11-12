//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_LANGE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_FUNCTIONS_LANGE_HPP_INCLUDED

#include <nt2/linalg/functions/lange.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/lapack/lange.hpp>
#include <nt2/sdk/memory/container.hpp>

#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
    typedef typename A0::value_type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

     if(a1 == 'I' || 'i')
     {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(dlange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(dlange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

      if(a1 == 'I' || 'i')
      {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(slange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(slange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

     if(a1 == 'I' || 'i')
     {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(zlange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(zlange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lange_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)             //  norm
                            )
  {
     typedef typename A0::value_type v_t;
     typedef typename nt2::meta::as_real<v_t>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 a1) const
    {
      result_type norm;
      nt2_la_int m = nt2::height(a0);
      nt2_la_int n = nt2::width(a0);
      nt2_la_int ld = m;

      if(a1 == 'I' || 'i')
      {
        nt2::memory::container<tag::table_, result_type, nt2::_2D> work(nt2::of_size(m,1));
        norm = NT2_F77NAME(clange)( &a1, &m, &n, a0.raw(), &ld, work.raw());
      }
      else
      {
        norm = NT2_F77NAME(clange)( &a1, &m, &n, a0.raw(), &ld, 0);
      }

      return norm;
    }
  };
} }

#endif
