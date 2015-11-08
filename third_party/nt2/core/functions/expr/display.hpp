//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DISPLAY_HPP_INCLUDED

#include <iostream>
#include <nt2/core/container/io.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0) const
    {
      nt2::details::disp("ans",std::cout,a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      nt2::details::disp(a0,std::cout,a1);
    }
  };
} }

#endif
