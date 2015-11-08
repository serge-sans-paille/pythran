//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FIRSTOFLENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FIRSTOFLENGTH_HPP_INCLUDED

#include <nt2/core/functions/firstoflength.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::firstoflength_, tag::cpu_
                            , (A0)(A1), ((ast_<A0, nt2::container::domain>))(scalar_<integer_<A1> > )
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& dim) const
    {
      return firstoflength(a0.extent(), dim);
    }
  };
} }

#endif
