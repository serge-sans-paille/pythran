//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_TRI1U_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_TRI1U_HPP_INCLUDED

#include <nt2/core/functions/tri1u.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tri1u_, tag::cpu_, (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 k) const
    {
      return k == 0 ? One<result_type>() : (k > 0) ? Zero<result_type>() : a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tri1u_, tag::cpu_, (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return One<result_type>();
    }
  };
} }

#endif
