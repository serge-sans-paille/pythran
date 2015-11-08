//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_ASSIGN_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_ASSIGN_HPP_INCLUDED

#include <nt2/memory/functions/assign.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/meta/real_of.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::assign_, tag::cpu_
                               , (A0)(A1)
                               , (is_same<A1, typename nt2::meta::real_of<A0>::type>)
                               , (generic_< complex_< unspecified_<A0> > >)
                                 (generic_< unspecified_<A1> >)
                               )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      return a0 = A0(a1);
    }
  };
} }

#endif
