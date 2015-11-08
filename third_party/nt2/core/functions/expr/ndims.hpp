//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NDIMS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NDIMS_HPP_INCLUDED

#include <nt2/core/functions/ndims.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ndims_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      typedef typename A0::extent_type extent_type;
      extent_type sz  = a0.extent();
      std::size_t i = sz.size();

      // If less than 2D, then return 2 directly
      if(i < 2) return 2;

      std::size_t d = nt2::ndims(sz);

      // ndims is either 2, |c-e| or, if d is 0, sz.size()
      return d ? ( (d < 2) ? 2 : d) : i;
    }
  };
} }

#endif
