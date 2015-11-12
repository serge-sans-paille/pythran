//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_SCALAR_ISEQUALN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_SCALAR_ISEQUALN_HPP_INCLUDED

#include <nt2/predicates/functions/isequaln.hpp>
#include <nt2/include/functions/is_equal_with_equal_nans.hpp>
#include <boost/simd/include/functions/all.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A0& a1) const
    {
      return is_equal_with_equal_nans(a0,a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return a0 == a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_< unspecified_<A0>, X>))
                              ((simd_< unspecified_<A1>, X>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return boost::simd::all(is_equal_with_equal_nans(a0, a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)(A1)(X)(T0)(N0)(T1)(N1)
                            , ((expr_< simd_< unspecified_<A0>, X>, T0, N0>))
                              ((expr_< simd_< unspecified_<A1>, X>, T1, N1>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return boost::simd::all(is_equal_with_equal_nans(a0, a1))();
    }
  };
} }

#endif
