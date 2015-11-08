//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_LOG2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_LOG2_HPP_INCLUDED

#include <nt2/exponential/functions/log2.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <nt2/exponential/functions/scalar/impl/logarithm.hpp>
#include <nt2/exponential/functions/simd/common/impl/logarithm.hpp>
#include <nt2/include/functions/simd/frexp.hpp>
#include <nt2/include/functions/simd/ilog2.hpp>
#include <nt2/include/functions/simd/log2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE NT2_FUNCTOR_CALL(1)
    {
      return nt2::ilog2(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1) const
    {
      return frexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< integer_<A2> >)
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2& a2) const
    {
      return frexp(a0, a1, a2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    typedef typename boost::simd::meta::is_native<A0>::type is_native_t;
    BOOST_FORCEINLINE NT2_FUNCTOR_CALL(1)
    {
      return details::logarithm<A0,is_native_t>::log2(a0);
    }
  };
} }

#endif
