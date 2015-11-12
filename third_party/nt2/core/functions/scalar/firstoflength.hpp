//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FIRSTOFLENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FIRSTOFLENGTH_HPP_INCLUDED

#include <nt2/core/functions/firstoflength.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::firstoflength_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef std::size_t       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 n) const
    {
      return n == A1(1) ? 1u : 0u;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::firstoflength_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef std::size_t       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 n) const
    {
      for(std::size_t i = 0; i < a0.size(); ++i)
        if(a0[i] == size_t(n)) return i+1;

      return 0;
    }
  };
} }

#endif
