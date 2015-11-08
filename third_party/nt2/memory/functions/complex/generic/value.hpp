//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_VALUE_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_VALUE_HPP_INCLUDED

#include <nt2/memory/functions/value.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::value_, tag::cpu_
                            , (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename A0::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0();
    }
  };
} }

#endif
