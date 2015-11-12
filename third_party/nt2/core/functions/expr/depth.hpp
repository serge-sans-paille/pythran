//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DEPTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DEPTH_HPP_INCLUDED

#include <nt2/core/functions/depth.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::depth_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::size(a0, 3);
    }
  };
} }

#endif
