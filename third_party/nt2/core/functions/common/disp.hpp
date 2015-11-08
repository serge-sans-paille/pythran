//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_DISP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_DISP_HPP_INCLUDED

#include <nt2/core/functions/disp.hpp>
#include <nt2/include/functions/disp.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::disp_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0) const
    {
      if(!nt2::isempty(a0)) std::cout << a0 << std::endl;
    }
  };
} }

#endif
