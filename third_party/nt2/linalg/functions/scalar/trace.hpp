//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_TRACE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_TRACE_HPP_INCLUDED
#include <nt2/linalg/functions/trace.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/diag_of.hpp>

//sum of diagonal elements even if a is not square

namespace nt2{ namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trace_, tag::cpu_,
                                (A0)
                                ,((ast_<A0, nt2::container::domain>))
                                )
  {
    typedef typename A0::value_type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(ismatrix(a0), "a0 is not a matrix or vector in trace call");
      result_type r = nt2::sum(nt2::diag_of(a0)(nt2::_)); //TODO
      return r;
    }
  };
} }

#endif
